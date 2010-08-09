#ifndef NB_VALUE_H
#define NB_VALUE_H

#include <sys/types.h>
#include "os.h"



typedef u_int32_t               nb_int_t;     /* generic integer          */
typedef double                  nb_num_t;     /* generic fp number        */
typedef u_int8_t                nb_u8_t;      /* generic 8 bit integer    */
typedef u_int16_t               nb_u16_t;     /* generic 16 bit integer   */
typedef u_int32_t               nb_u32_t;     /* generic 32 bit integer   */
typedef u_int64_t               nb_u64_t;     /* generic 64 bit integer   */
typedef unsigned char           nb_bool_t;    /* boolean true/false       */
typedef unsigned char           nb_char_t;    /* single character         */
typedef unsigned long           nb_uint_t;    /* generic unsigned int     */
typedef char                  * nb_cstr_p;    /* C string                 */


/* This is based on the value tags (nunboxing) used in Mozilla JS
 * http://hg.mozilla.org/tracemonkey/raw-file/898ab54a0ce9/js/src/jsval.h
 */

typedef union {
    nb_int_t      integer;
    nb_bool_t     boolean;
} nb_payload_t;

typedef struct {
    nb_payload_t  value;
    nb_u32_t      type;           /* FIXME: assumes little-endian */
} nb_tagged_t;

typedef union {
    nb_u64_t      bits;
    nb_num_t      number;
    nb_tagged_t   tagged;
} nb_value_t;


/* As per IEEE-754 double precision numbers, the first bit is the sign bit,
 * the next 11 bits are the exponent and the remaining 52 are used to encode
 * the mantissa.  If all of the first 12 (sign + exponent) bits are 1 then 
 * the value represents +/- Infinity when all of the mantissa bits are 0, or
 * NaN if any of the mantissa bits are 1.  So setting the first 13 bits to 1 
 * will always represent NaN and we can use the remaining 51 bits to encode
 * some other kind of payload.  This widely used technique is commonly known 
 * as "NaN-boxing".
 *
 * In those 51 bits we can store a 32 bit integer.  We can also store a 
 * memory pointer.  On 32 bit architectures that also requires 32 bits.  On
 * all widely used (at the time of writing) 64-bit platforms, (up to) 47 bits 
 * are used to store memory adddresses.  That leaves us 4 bits spare which we
 * can use to encode up to 16 different data types.
 */

#define NB_NAN_MASK           0xFFF8000000000000LL
#define NB_PAYLOAD_MASK       0x00007FFFFFFFFFFFLL
#define NB_PAYLOAD_BITS       47
#define NB_PAYLOAD(v)         (v.bits & NB_PAYLOAD_MASK)

#define NB_TYPE_BITS          4
#define NB_TYPE_MASK          0x0F
#define NB_TYPE_UP(t)         ((nb_u64_t) (t & NB_TYPE_MASK) << NB_PAYLOAD_BITS)
#define NB_TYPE_DOWN(v)       ((nb_u8_t)  (v >> NB_PAYLOAD_BITS) & NB_TYPE_MASK)

#define NB_TAG_NUM_TYPE       ((nb_u8_t)  0x00)     /* 64 bit double    */
#define NB_TAG_INT_TYPE       ((nb_u8_t)  0x01)     /* 32 bit integer   */
#define NB_TAG_STR_TYPE       ((nb_u8_t)  0x02)     /* string pointer   */

#define NB_TAG_NAN_MASK(t)    (NB_NAN_MASK | NB_TYPE_UP(t))
#define NB_TAG_NUM_MASK       ((nb_u64_t) NB_TAG_NUM_TYPE)
#define NB_TAG_INT_MASK       NB_TAG_NAN_MASK(NB_TAG_INT_TYPE)
#define NB_TAG_STR_MASK       NB_TAG_NAN_MASK(NB_TAG_STR_TYPE)

#define NB_TAG_TYPEOF(v)      NB_TYPE_DOWN(v.bits)
#define NB_TAG_IS_TYPE(v,t)   ((nb_bool_t) NB_TAG_TYPEOF(v) == t)
#define NB_TAG_IS_NUM(v)      ((nb_bool_t) ((nb_u64_t) v.bits < NB_NAN_MASK))
#define NB_TAG_IS_INT(v)      NB_TAG_IS_TYPE(v, NB_TAG_INT_TYPE)
#define NB_TAG_IS_STR(v)      NB_TAG_IS_TYPE(v, NB_TAG_STR_TYPE)
#define NB_TAG_IS_TAGGED(v)   (! NB_TAG_IS_NUM(v))
//#define NB_TAG_IS_TYPE(v,t)   (! NB_TAG_IS_NUM(t))



/*--------------------------------------------------------------------------
 * inline functions to encode native values as tagged values
 *--------------------------------------------------------------------------*/

static NB_DO_INLINE nb_value_t
NB_NUM_VAL(nb_num_t n) {
    nb_value_t v;
    v.number = n;
    return v;
}

static NB_DO_INLINE nb_value_t
NB_INT_VAL(nb_int_t i) {
    nb_value_t v;
    v.bits = NB_TAG_INT_MASK | (nb_u64_t) i;
    return v;
}

static NB_DO_INLINE nb_value_t
NB_STR_VAL(nb_cstr_p s) {
    nb_value_t v;
    v.bits = NB_TAG_STR_MASK | (nb_u64_t) s;
    return v;
}


/*--------------------------------------------------------------------------
 * inline functions to decode tagged values to native values
 * 
 *--------------------------------------------------------------------------*/

static NB_DO_INLINE nb_num_t
NB_VAL_NUM(nb_value_t v) {
    return v.number;
}

static NB_DO_INLINE nb_int_t
NB_VAL_INT(nb_value_t v) {
    return (nb_int_t) v.bits;
}

static NB_DO_INLINE nb_cstr_p
NB_VAL_STR(nb_value_t v) {
    return (nb_cstr_p) NB_PAYLOAD(v);
}

//#define NB_TAG_NAN_MASK32     ((nb_u32_t) 0xFFF80000L)
//#define NB_TAG_IS_NUM(t)

void nb_dump_u64(nb_u64_t value);
void nb_dump_64(nb_u64_t value);
void nb_dump_32(nb_u32_t value);
void nb_dump_value(nb_value_t value);

#endif /* NB_VALUE_H */

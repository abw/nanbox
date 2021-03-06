#ifndef HEMP_TYPES_H
#define HEMP_TYPES_H

/*--------------------------------------------------------------------------
 * Naming conventions (more to avoid namespace collision than to enforce
 * a Hungarian-like notation):
 *  - Basic data types have a '_t' suffix, e.g. hemp_bool_t
 *  - Pointers have a '_p' suffix, e.g. hemp_element_p
 *  - Structures have a '_s' suffix, e.g. hemp_element_s
 *  - Unions have a '_u' suffix, e.g. hemp_evalue_u
 *  - Enums have a '_e' suffix, e.g. hemp_tag_style_e
 *  - Function pointers have a '_f' suffix, e.g. hemp_scan_f
 *--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
 * generic data types
 *--------------------------------------------------------------------------*/

typedef u_int8_t                hemp_u8_t;      /* generic 8 bit integer    */
typedef u_int16_t               hemp_u16_t;     /* generic 16 bit integer   */
typedef u_int32_t               hemp_u32_t;     /* generic 32 bit integer   */
typedef u_int64_t               hemp_u64_t;     /* generic 64 bit integer   */
typedef unsigned char           hemp_bool_t;    /* boolean true/false       */
typedef unsigned char           hemp_char_t;    /* single character         */
typedef long                    hemp_flags_t;   /* bitmask                  */
typedef long                    hemp_offset_t;  /* -ve/+ve offset           */
typedef u_int32_t               hemp_int_t;     /* generic integer          */
typedef double                  hemp_num_t;     /* generic fp number        */
typedef unsigned long           hemp_uint_t;    /* generic unsigned int     */
typedef unsigned long           hemp_size_t;    /* +ve size of list         */
typedef unsigned long           hemp_pos_t;     /* +ve posn. in string/list */
typedef unsigned short int      hemp_prec_t;    /* operator precedence      */
typedef jmp_buf                 hemp_jump_b;    /* longjmp buffer           */
typedef struct hemp_jump_s      hemp_jump_t;    /* longjmp call chain       */ 


/*--------------------------------------------------------------------------
 * generic pointers
 *--------------------------------------------------------------------------*/

typedef void                    * hemp_mem_p;     /* generic memory pointer   */
typedef char                    * hemp_cstr_p;    /* C string                 */
typedef const char              * hemp_name_p;    /* immutable C string       */


/*--------------------------------------------------------------------------
 * hemp data structures
 *--------------------------------------------------------------------------*/

typedef struct hemp_s           * hemp_p;
typedef struct hemp_action_s    * hemp_action_p;
typedef struct hemp_dialect_s   * hemp_dialect_p;
typedef struct hemp_element_s   * hemp_element_p;
typedef struct hemp_elements_s  * hemp_elements_p;
typedef struct hemp_etype_s     * hemp_etype_p;
typedef struct hemp_error_s     * hemp_error_p;
typedef struct hemp_factory_s   * hemp_factory_p;
typedef struct hemp_filesystem_s *hemp_filesystem_p;
typedef struct hemp_grammar_s   * hemp_grammar_p;
typedef struct hemp_hash_s      * hemp_hash_p;
typedef struct hemp_hash_item_s * hemp_hash_item_p;
typedef struct hemp_jump_s      * hemp_jump_p;
typedef struct hemp_language_s  * hemp_language_p;
typedef struct hemp_list_s      * hemp_list_p;
typedef struct hemp_pnode_s     * hemp_pnode_p;
typedef struct hemp_pool_s      * hemp_pool_p;
typedef struct hemp_ptree_s     * hemp_ptree_p;
typedef struct hemp_scheme_s    * hemp_scheme_p;
typedef struct hemp_scope_s     * hemp_scope_p;
typedef struct hemp_slab_s      * hemp_slab_p;
typedef struct hemp_source_s    * hemp_source_p;
typedef struct hemp_symbol_s    * hemp_symbol_p;
typedef struct hemp_symbols_s   * hemp_symbols_p;
typedef struct hemp_tag_s       * hemp_tag_p;
typedef struct hemp_tagset_s    * hemp_tagset_p;
typedef struct hemp_template_s  * hemp_template_p;
typedef struct hemp_text_s      * hemp_text_p;
typedef struct hemp_type_s      * hemp_type_p;


typedef enum   hemp_tag_style_e   hemp_tag_style_t;

typedef union  hemp_evalue_u      hemp_evalue_t;
typedef struct hemp_unary_s       hemp_unary_t;
typedef struct hemp_binary_s      hemp_binary_t;
typedef struct hemp_block_s       hemp_block_t;


/*
typedef struct hemp_context     * hemp_context_t;
typedef struct hemp_elements    * hemp_elements_t;
typedef struct hemp_hub         * hemp_hub_t;
typedef struct hemp_scheme      * hemp_scheme_t;
typedef struct hemp_scope       * hemp_scope_t;
typedef struct hemp_source      * hemp_source_t;
typedef struct hemp_text        * hemp_text_t;
typedef struct hemp_type        * hemp_type_t;
typedef struct hemp_vtype       * hemp_vtype_t;
typedef struct hemp_vtypes      * hemp_vtypes_t;
typedef struct hemp_value       * hemp_value_t;

typedef struct hemp_templates_s * hemp_templates_p;
*/


/*--------------------------------------------------------------------------
 * main hemp data structure
 *--------------------------------------------------------------------------*/

struct hemp_s {
    hemp_factory_p   languages;
    hemp_factory_p   elements;
    hemp_factory_p   grammars;
    hemp_factory_p   dialects;

    hemp_hash_p      schemes;
//  hemp_hash_p      tags;
    hemp_hash_p      templates;
    hemp_dialect_p   dialect;

    hemp_bool_t      verbose;
    hemp_bool_t      debug;
//  hemp_hash_t dialect_factory;
    hemp_jump_p      jump;
    hemp_error_p     error;
    hemp_cstr_p     *errmsg;
};

/*--------------------------------------------------------------------------
 * function pointers
 *--------------------------------------------------------------------------*/

typedef hemp_bool_t     
    (* hemp_list_each_f)(           /* function called against list items   */
        hemp_list_p     list,       /* pointer to list                      */ 
        hemp_pos_t      index,      /* 0-based index of item in list        */
        hemp_mem_p      item        /* pointer to item itself               */
    );

typedef hemp_bool_t     
    (* hemp_hash_each_f)(           /* function called against hash items   */
        hemp_hash_p      hash,      /* pointer to hash                      */ 
        hemp_pos_t       index,     /* 0-based index of item in hash        */
        hemp_hash_item_p item       /* pointer to hash item entry           */
    );

typedef hemp_symbol_p
    (* hemp_symbol_f)(
        hemp_p        hemp,         /* pointer to current hemp context      */
        hemp_symbol_p symbol        /* pointer to new symbol to initialise  */
    );

typedef hemp_dialect_p 
    (* hemp_dialect_f)(
        hemp_dialect_p dialect      /* pointer to dialect to prepare       */
    );

// TODO: rename this to hemp_template_f
typedef hemp_template_p 
    (* hemp_prep_f)(
        hemp_template_p template    /* pointer to template to prepare       */
    );

typedef hemp_bool_t 
    (* hemp_scan_f)(
        hemp_template_p template    /* pointer to template to scan          */
    );

typedef void
    (* hemp_clean_f)(
        hemp_mem_p item             /* pointer to object to clean           */
    );

typedef hemp_mem_p
    (* hemp_actor_f)(
        hemp_mem_p argument, 
        ...
    );

//typedef void
//    (* hemp_eclean_f)(
//        hemp_element_p element      /* pointer to element to clean          */
//    );

// HEMP_TAG_SCAN_ARGS                                                  \
//    hemp_template_p template,   /* current template                     */  \
//    hemp_tag_p      tag,        /* pointer to current tag               */  \
//    hemp_cstr_p     tagtok,     /* pointer to tag start token in source */  \
//    hemp_pos_t      pos,        /* byte position of tag in source       */  \
//    hemp_cstr_p    *srcptr      /* pointer to source position pointer   */

#define HEMP_TAG_SCAN_ARGS    \
    hemp_template_p tmpl,     \
    hemp_tag_p      tag,      \
    hemp_cstr_p     tagtok,   \
    hemp_pos_t      pos,      \
    hemp_cstr_p    *srcptr    

typedef void 
    (* hemp_tag_scan_f)(
        HEMP_TAG_SCAN_ARGS
    );

typedef hemp_element_p
    (* hemp_sym_scan_f)(
        HEMP_TAG_SCAN_ARGS,
        hemp_symbol_p symbol
    );

typedef hemp_element_p
    (* hemp_skip_f )( 
        hemp_element_p *current     /* pointer to current element pointer   */
    );

typedef hemp_element_p  
    (* hemp_expr_f )(
        hemp_element_p *current,    /* pointer to current element pointer   */
        hemp_scope_p    scope,      /* current lexical scope                */
        hemp_prec_t     precedence, /* operator precedence level            */
        hemp_bool_t     force       /* yes, really parse something          */
);

typedef hemp_element_p  
    (* hemp_infix_f )(
        hemp_element_p *current,    /* pointer to current element pointer   */
        hemp_scope_p    scope,      /* current lexical scope                */
        hemp_prec_t     precedence, /* operator precedence level            */
        hemp_bool_t     force,      /* yes, really parse something          */
        hemp_element_p  element     /* preceding element                    */
);

typedef hemp_text_p 
    (* hemp_text_f )(
        hemp_element_p  element,    /* pointer to element                   */
        hemp_text_p     buffer      /* optional pointer to output buffer    */
    );


typedef hemp_cstr_p     (* hemp_source_namer_f   )( hemp_source_p );
typedef hemp_bool_t     (* hemp_source_checker_f )( hemp_source_p );
typedef hemp_cstr_p     (* hemp_source_reader_f  )( hemp_source_p );


/*
typedef hemp_bool_t     (* hemp_scan_fn)(hemp_template_t);
typedef hemp_cstr_t     (* hemp_source_text_fn)(hemp_source_t);
typedef hemp_bool_t     (* hemp_source_bool_fn)(hemp_source_t);
typedef hemp_bool_t     (* hemp_build_fn)(hemp_t);
typedef hemp_bool_t     (* hemp_onload_fn)(hemp_t);
*/

//typedef hemp_value_t    (* hemp_init_fn)();
/*
typedef void            (* hemp_free_fn)(hemp_value_t);
typedef hemp_bool_t     (* hemp_truth_fn)(hemp_value_t);
typedef hemp_value_t    (* hemp_unary_fn)(hemp_value_t);
typedef hemp_value_t    (* hemp_binary_fn)(hemp_value_t, hemp_value_t);
typedef hemp_value_t    (* hemp_ternary_fn)(hemp_value_t, hemp_value_t, hemp_value_t);

typedef hemp_text_t     (* hemp_text_fn)(hemp_element_t, hemp_text_t);
*/

/* old object type methods, being replace by those below... */
/*
typedef hemp_ptr_t      (* hemp_init_fn)(hemp_type_t, va_list *args);
typedef void            (* hemp_wipe_fn)(hemp_ptr_t);
*/

/* new object type methods, maybe not being replaced after all... */
/*
typedef hemp_item_t     (* hemp_acquire_fn)(hemp_type_t type);
typedef hemp_bool_t     (* hemp_prepare_fn)(hemp_item_t item, va_list *args);
typedef hemp_bool_t     (* hemp_cleanup_fn)(hemp_item_t item);
typedef void            (* hemp_release_fn)(hemp_item_t item);
*/



#endif /* HEMP_TYPES_H */
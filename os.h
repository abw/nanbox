#ifndef NB_OS_H
#define NB_OS_H


#define NB_ARCH_X86           32
#define NB_ARCH_X64           64
#define NB_ARCH_LITTLE_ENDIAN 1234
#define NB_ARCH_BIG_ENDIAN    4321


#ifndef NB_TARGET
    #if defined(i386) || defined(__i386) || defined(__i386__) || defined(_M_IX86)
        #define NB_TARGET     NB_ARCH_X86
    #elif defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) || defined (_M_IA64)
        #define NB_TARGET     NB_ARCH_X64
    #else
        #error "No support for this architecture (yet)"
    #endif
#endif

#if NB_TARGET == NB_ARCH_X86
    #define NB_ARCH_NAME      "x86"
    #define NB_ARCH_BITS      32
#elif NB_TARGET == NB_ARCH_X64
    #define NB_ARCH_NAME      "x64"
    #define NB_ARCH_BITS      64
#else
    #error "No target architecture defined"
#endif

#if __LITTLE_ENDIAN__ || NB_TARGET == NB_ARCH_X86 || NB_TARGET == NB_ARCH_X64
    #define NB_BYTE_ORDER     NB_ARCH_LITTLE_ENDIAN
#elif __BIG_ENDIAN__
    #define NB_BYTE_ORDER     NB_ARCH_BIG_ENDIAN
#else
    #error "Can't determine the endian-ness of the target architecture"
#endif

#if NB_BYTE_ORDER == NB_ARCH_LITTLE_ENDIAN
    #define NB_LITTLE_ENDIAN  1
    #define NB_BIG_ENDIAN     0
    #define NB_ENDIAN         "little"
#elif NB_BYTE_ORDER == NB_ARCH_BIG_ENDIAN
    #define NB_LITTLE_ENDIAN  0
    #define NB_BIG_ENDIAN     1
    #define NB_ENDIAN         "big"
#else
    #error "No endianness defined for the target architecture"
#endif

#ifndef NB_INLINE
    #if defined __cplusplus
        #define NB_INLINE     inline
    #elif defined __GNUC__
        #define NB_INLINE     __inline__
    #elif defined _MSC_VER
        #define NB_INLINE     __inline
    #else
        #define NB_INLINE     inline
    # endif
#endif

#ifndef NB_DO_INLINE
    #if defined __GNUC__
        #define NB_DO_INLINE  __attribute__((always_inline)) NB_INLINE
    #elif defined _MSC_VER
        #define NB_DO_INLINE  __forceinline
    #else
        #define NB_DO_INLINE  NB_INLINE
    #endif
#endif

#ifndef NB_NO_INLINE
    #if defined __GNUC__
        #define NB_NO_INLINE  __attribute__((noinline))
    #elif defined _MSC_VER
        #define NB_NO_INLINE  __declspec(noinline)
    #else
        #define NB_NO_INLINE
    #endif
#endif


#endif /* NB_OS_H */
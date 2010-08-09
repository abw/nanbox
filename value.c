#include <stdio.h>
#include "debug.h"
#include "value.h"


void nb_dump_value(
    nb_value_t tvalue
) {
    nb_dump_u64(tvalue.bits);
}


void nb_dump_u64(
    nb_u64_t  value
) {
    nb_u64_t  mask  = (nb_u64_t) 1 << 63;
    nb_u64_t  bit;
    nb_int_t  n = 1;
    nb_cstr_p col;
    printf("0x%016llx\n", value);

    while (mask) {
        bit = value & mask;
        mask = mask >> 1;
        if (n == 1) {
            col = ANSI_MAGENTA;
        }
        else if (n < 13) {
            col = ANSI_YELLOW;
        }
        else if (n < 14) {
            col = ANSI_MAGENTA;
        }
        else if (n < 18) {
            col = ANSI_BLUE;
        }
        else {
            col = ANSI_CYAN;
        }
        printf("%s%c", col, bit ? '1' : '0');
        if (n % 4 == 0)
            printf(" ");
        n++;
    }
    printf(ANSI_RESET "\n");
//    nb_dump_32((nb_u32_t)(value >> 32));
//    nb_dump_32((nb_u32_t)(nb_u64_t) value & 0xFFFFFFFFL);
}

void nb_dump_64(
    nb_u64_t value
) {
    nb_u64_t top = value & 0xffffffff00000000LL;
    top = top >> 32;
    nb_u64_t bot = value & 0xffffffffL;
    printf("0x%016llx\n", value);
//    printf("TOP: 0x%016llx\n", top);
    nb_dump_32((nb_u32_t) top);
    nb_dump_32((nb_u32_t) bot);
    printf("\n");
}

void nb_dump_32(
    nb_u32_t value
) {
    nb_u32_t  mask  = (nb_u32_t) 1 << 31;
    nb_u32_t bit;
    printf("0x%08x : ", value);

    while (mask) {
        bit = value & mask;
        mask = mask >> 1;
        printf("%c", bit ? '1' : '0');
    }
    printf("\n");
}


#include <stdio.h>
#include "value.h"
#include "debug.h"
#include "tap.h"


void test_value();

int
main(
    int  argc, 
    char **argv, 
    char **env)
{
    printf("%s %d bits %s endian\n", NB_ARCH_NAME, NB_ARCH_BITS, NB_ENDIAN);
    plan_tests(10);
    test_value();
    return exit_status();
}


void test_value() {
    pass("testing value");
    nb_value_t value;

    printf("NUM64:\n");
    nb_dump_u64(NB_TAG_NUM_MASK);
    printf("NAN64:\n");
    nb_dump_u64(NB_NAN_MASK);
    printf("INT64:\n");
    nb_dump_u64(NB_TAG_INT_MASK);
    printf("STR64:\n");
    nb_dump_u64(NB_TAG_STR_MASK);

    /* native double */
    printf("FLOAT: 3.14159\n");
    nb_num_t expect = -314.59;
    value = NB_NUM_VAL(expect);
    nb_dump_value(value);

    nb_num_t n = NB_VAL_NUM(value);
    ok( ! NB_TAG_IS_TAGGED(value), "number is not a tagged value" );
    ok( NB_TAG_IS_NUM(value), "number is a number value" );
    ok( n == expect, "got num value back" );

    /* tagged int */
    printf("INT: 12345\n");
    value = NB_INT_VAL(12345);
    nb_dump_value(value);

    nb_u32_t i = NB_VAL_INT(value);
    ok( NB_TAG_IS_TAGGED(value), "integer is a tagged value" );
    ok( NB_TAG_IS_INT(value), "integer is an integer value" );
    ok( i == 12345, "got int value back" );

    /* tagged string pointer */
    nb_cstr_p es = "Hello world!\n";
    printf("STRING: %s\n", es);
    value = NB_STR_VAL(es);
    nb_dump_value(value);

    nb_cstr_p s = NB_VAL_STR(value);
    printf("[%p]   [%p]\n", es, s);
    ok( NB_TAG_IS_TAGGED(value), "string is a tagged value" );
    ok( NB_TAG_IS_STR(value), "string is a string value" );
    is( s, es, "got str value back" );
}


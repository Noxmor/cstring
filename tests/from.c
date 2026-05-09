#include "test.h"

int main()
{
    cstring_t empty = cstring_from("");

    TEST_ASSERT(cstring_len(&empty) == 0);
    TEST_ASSERT(strcmp(cstring_cstr(&empty), "") == 0);

    TEST_MAKE_SSO_STRING(less);
    cstring_t less_str = cstring_from(less);

    TEST_ASSERT(cstring_len(&less_str) == strlen(less));
    TEST_ASSERT(strcmp(cstring_cstr(&less_str), less) == 0);

    TEST_MAKE_STRING(exact, CSTRING_SSO_CAPACITY);
    cstring_t exact_str = cstring_from(exact);

    TEST_ASSERT(cstring_len(&exact_str) == CSTRING_SSO_CAPACITY - 1);
    TEST_ASSERT(strcmp(cstring_cstr(&exact_str), exact) == 0);

    TEST_MAKE_HEAP_STRING(more);
    cstring_t more_str = cstring_from(more);

    TEST_ASSERT(cstring_len(&more_str) == strlen(more));
    TEST_ASSERT(strcmp(cstring_cstr(&more_str), more) == 0);

    cstring_free(&empty);
    cstring_free(&less_str);
    cstring_free(&exact_str);
    cstring_free(&more_str);

    return EXIT_SUCCESS;
}

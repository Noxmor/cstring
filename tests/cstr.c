#include "test.h"

int main()
{
    TEST_MAKE_SSO_STRING(less);
    TEST_MAKE_STRING(exact, CSTRING_SSO_CAPACITY);
    TEST_MAKE_HEAP_STRING(more);

    cstring_t empty_str = cstring_from("");
    cstring_t less_str = cstring_from(less);
    cstring_t exact_str = cstring_from(exact);
    cstring_t more_str = cstring_from(more);

    TEST_ASSERT(strcmp(cstring_cstr(&empty_str), "") == 0);
    TEST_ASSERT(strcmp(cstring_cstr(&less_str), less) == 0);
    TEST_ASSERT(strcmp(cstring_cstr(&exact_str), exact) == 0);
    TEST_ASSERT(strcmp(cstring_cstr(&more_str), more) == 0);

    cstring_free(&empty_str);
    cstring_free(&less_str);
    cstring_free(&exact_str);
    cstring_free(&more_str);

    return EXIT_SUCCESS;
}

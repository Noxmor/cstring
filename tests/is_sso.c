#include "test.h"

int main()
{
    TEST_MAKE_SSO_STRING(str0);
    TEST_MAKE_STRING(str1, CSTRING_SSO_CAPACITY);
    TEST_MAKE_HEAP_STRING(str2);

    cstring_t empty = cstring_from("");
    cstring_t less = cstring_from(str0);
    cstring_t exact = cstring_from(str1);
    cstring_t more = cstring_from(str2);

    TEST_ASSERT(cstring_is_sso(&empty));
    TEST_ASSERT(cstring_is_sso(&less));
    TEST_ASSERT(cstring_is_sso(&exact));
    TEST_ASSERT(!cstring_is_sso(&more));

    cstring_free(&empty);
    cstring_free(&less);
    cstring_free(&exact);
    cstring_free(&more);

    return EXIT_SUCCESS;
}

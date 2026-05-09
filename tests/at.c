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

    for (size_t i = 0; i < cstring_len(&empty_str); ++i)
    {
        TEST_ASSERT(cstring_at(&empty_str, i) == ""[i]);
    }

    for (size_t i = 0; i < cstring_len(&less_str); ++i)
    {
        TEST_ASSERT(cstring_at(&less_str, i) == less[i]);
    }

    for (size_t i = 0; i < cstring_len(&exact_str); ++i)
    {
        TEST_ASSERT(cstring_at(&exact_str, i) == exact[i]);
    }

    for (size_t i = 0; i < cstring_len(&more_str); ++i)
    {
        TEST_ASSERT(cstring_at(&more_str, i) == more[i]);
    }

    cstring_free(&empty_str);
    cstring_free(&less_str);
    cstring_free(&exact_str);
    cstring_free(&more_str);

    return EXIT_SUCCESS;
}

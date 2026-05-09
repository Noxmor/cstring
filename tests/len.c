#include "test.h"

int main()
{
    for (size_t i = 1; i < CSTRING_SSO_CAPACITY * 2; ++i)
    {
        TEST_MAKE_STRING(str, i);

        cstring_t s = cstring_from(str);

        TEST_ASSERT(cstring_len(&s) == i - 1);

        cstring_free(&s);
    }

    cstring_t s = cstring_from("");

    TEST_ASSERT(cstring_len(&s) == 0);

    cstring_free(&s);

    return EXIT_SUCCESS;
}

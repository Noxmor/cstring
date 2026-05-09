#include "test.h"

int main()
{
    cstring_t str = cstring_empty();

    for (size_t i = 0; i < CSTRING_SSO_CAPACITY * 2; ++i)
    {
        cstring_reserve(&str, i);

        TEST_ASSERT(cstring_capacity(&str) == i || (cstring_capacity(&str) == CSTRING_SSO_CAPACITY && i <= CSTRING_SSO_CAPACITY));
    }

    const size_t capacity = cstring_capacity(&str);

    for (size_t i = 0; i < CSTRING_SSO_CAPACITY * 2; ++i)
    {
        cstring_reserve(&str, capacity - i);

        TEST_ASSERT(cstring_capacity(&str) == capacity);
    }

    cstring_free(&str);

    return EXIT_SUCCESS;
}

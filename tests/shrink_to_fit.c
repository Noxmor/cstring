#include "test.h"

int main()
{
    const char* s = "Hello, World!";

    cstring_t str = cstring_empty();
    cstring_t hello_world = cstring_from(s);

    const size_t capacity = strlen(s) + 1;
    cstring_reserve(&str, capacity);
    cstring_shrink_to_fit(&str);
    TEST_ASSERT(cstring_capacity(&str) == CSTRING_SSO_CAPACITY);

    cstring_reserve(&str, capacity * 2);
    cstring_concat(&str, &hello_world);
    cstring_shrink_to_fit(&str);
    TEST_ASSERT(cstring_capacity(&str) == cstring_capacity(&hello_world));

    cstring_free(&str);
    cstring_free(&hello_world);

    return EXIT_SUCCESS;
}

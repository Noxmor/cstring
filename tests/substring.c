#include "test.h"

int main()
{
    cstring_t empty = cstring_empty();
    cstring_t hello_world = cstring_from("Hello, World!");
    cstring_t hello = cstring_from("Hello");
    cstring_t world = cstring_from("World");

    cstring_t str1 = cstring_substring(&hello_world, 0, cstring_len(&hello_world));
    TEST_ASSERT(cstring_equals(&str1, &hello_world));

    cstring_t str2 = cstring_substring(&hello_world, 0, 5);
    TEST_ASSERT(cstring_equals(&str2, &hello));

    cstring_t str3 = cstring_substring(&hello_world, 7, 5);
    TEST_ASSERT(cstring_equals(&str3, &world));

    cstring_t str4 = cstring_substring(&hello_world, 3, 0);
    TEST_ASSERT(cstring_equals(&str4, &empty));

    cstring_free(&empty);
    cstring_free(&hello_world);
    cstring_free(&hello);
    cstring_free(&world);
    cstring_free(&str1);
    cstring_free(&str2);
    cstring_free(&str3);
    cstring_free(&str4);

    return EXIT_SUCCESS;
}

#include "test.h"

int main()
{
    cstring_t empty = cstring_empty();
    cstring_t foo = cstring_from("foo");
    cstring_t bar = cstring_from("bar");

    cstring_t str1 = cstring_empty();
    cstring_t str2 = cstring_copy(&bar);

    cstring_concat(&str1, &foo);
    TEST_ASSERT(cstring_equals(&str1, &foo));

    cstring_concat(&str2, &empty);
    TEST_ASSERT(cstring_equals(&str2, &bar));

    cstring_free(&empty);
    cstring_free(&foo);
    cstring_free(&bar);
    cstring_free(&str1);
    cstring_free(&str2);

    return EXIT_SUCCESS;
}

#include "test.h"

int main()
{
    cstring_t empty = cstring_empty();
    cstring_t foo = cstring_from("foo");
    cstring_t bar = cstring_from("bar");

    cstring_t oo = cstring_from("oo");
    cstring_t barf = cstring_from("barf");

    cstring_t str1 = cstring_empty();
    cstring_t str2 = cstring_copy(&bar);

    cstring_append(&str1, &foo, 1, 2);
    TEST_ASSERT(cstring_equals(&str1, &oo));

    cstring_append(&str2, &foo, 0, 1);
    TEST_ASSERT(cstring_equals(&str2, &barf));

    cstring_append(&str1, &empty, 0, 0);
    TEST_ASSERT(cstring_equals(&str1, &oo));

    cstring_free(&empty);
    cstring_free(&foo);
    cstring_free(&bar);
    cstring_free(&oo);
    cstring_free(&barf);
    cstring_free(&str1);
    cstring_free(&str2);

    return EXIT_SUCCESS;
}

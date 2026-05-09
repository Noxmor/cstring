#include "test.h"

int main()
{
    cstring_t str1 = cstring_from("foo");
    cstring_t str2 = cstring_copy(&str1);

    TEST_ASSERT(cstring_equals(&str1, &str2));

    cstring_free(&str1);

    TEST_ASSERT(strcmp(cstring_cstr(&str2), "foo") == 0);

    cstring_free(&str2);

    return EXIT_SUCCESS;
}

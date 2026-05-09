#include "test.h"

int main()
{
    cstring_t str1 = cstring_from("foo");
    cstring_t str2 = cstring_from("bar");
    cstring_t str3 = cstring_from("foo");

    TEST_ASSERT(!cstring_equals(&str1, &str2));
    TEST_ASSERT(cstring_equals(&str1, &str3));

    return EXIT_SUCCESS;
}

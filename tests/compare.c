#include "test.h"

int main()
{
    cstring_t str1 = cstring_from("foo");
    cstring_t str2 = cstring_from("bar");
    cstring_t str3 = cstring_from("foo");

    TEST_ASSERT(cstring_compare(&str1, &str2) == 'f' - 'b');
    TEST_ASSERT(cstring_compare(&str1, &str3) == 0);

    return EXIT_SUCCESS;
}

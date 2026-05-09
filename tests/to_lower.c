#include "test.h"

int main()
{
    cstring_t empty = cstring_from("");

    cstring_to_lower(&empty);
    TEST_ASSERT(strcmp(cstring_cstr(&empty), "") == 0);

    cstring_to_upper(&empty);
    TEST_ASSERT(strcmp(cstring_cstr(&empty), "") == 0);

    cstring_t lower = cstring_from("hello, world!");
    cstring_t upper = cstring_from("HELLO, WORLD!");

    cstring_to_lower(&lower);
    cstring_to_lower(&upper);

    TEST_ASSERT(cstring_equals(&lower, &upper));

    cstring_free(&empty);
    cstring_free(&lower);
    cstring_free(&upper);

    return EXIT_SUCCESS;
}

#include "test.h"

int main()
{
    cstring_t empty = cstring_empty();
    cstring_t foo = cstring_from("foo");

    TEST_ASSERT(cstring_find_char(&empty, '#') == CSTRING_NOT_FOUND);
    TEST_ASSERT(cstring_find_char(&foo, 'f') == 0);
    TEST_ASSERT(cstring_find_char(&foo, 'o') == 1);

    cstring_free(&empty);
    cstring_free(&foo);

    return EXIT_SUCCESS;
}

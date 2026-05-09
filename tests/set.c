#include "test.h"

int main()
{
    cstring_t hello1 = cstring_from("hello");
    cstring_t hello2 = cstring_from("Hello");
    cstring_t hell = cstring_from("Hell!");

    cstring_set(&hello1, 'H', 0);
    TEST_ASSERT(cstring_equals(&hello1, &hello2));

    cstring_set(&hello1, '!', 4);
    TEST_ASSERT(cstring_equals(&hello1, &hell));

    cstring_free(&hello1);
    cstring_free(&hello2);
    cstring_free(&hell);

    return EXIT_SUCCESS;
}

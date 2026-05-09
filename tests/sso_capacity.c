#include "test.h"

int main()
{
    cstring_t str = cstring_empty();

    TEST_ASSERT(sizeof(str.data) == CSTRING_SSO_CAPACITY);

    return EXIT_SUCCESS;
}

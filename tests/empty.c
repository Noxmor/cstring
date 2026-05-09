#include "test.h"

int main()
{
    cstring_t empty1 = cstring_empty();
    cstring_t empty2 = cstring_from("");

    TEST_ASSERT(memcmp(&empty1, &empty2, sizeof(cstring_t)) == 0);

    return EXIT_SUCCESS;
}

#include "test.h"
#include <string.h>

int main()
{
    TEST_MAKE_SSO_STRING(less);
    TEST_MAKE_HEAP_STRING(more);

    cstring_t zero_str = cstring_empty();
    cstring_t empty_str = cstring_from("");
    cstring_t sso_str = cstring_from(less);
    cstring_t heap_str = cstring_from(more);

    cstring_free(&empty_str);
    cstring_free(&sso_str);
    cstring_free(&heap_str);

    TEST_ASSERT(memcmp(&empty_str, &zero_str, sizeof(cstring_t)) == 0);
    TEST_ASSERT(memcmp(&sso_str, &zero_str, sizeof(cstring_t)) == 0);
    TEST_ASSERT(memcmp(&heap_str, &zero_str, sizeof(cstring_t)) == 0);

    return EXIT_SUCCESS;
}

#include <stddef.h>
static void oom_handler(size_t size);

#define CSTRING_OOM_HANDLER(size) oom_handler(size)
#define CSTRING_ALLOC(size) NULL
#include "test.h"

static size_t expected_size;

int main()
{
    TEST_MAKE_SSO_STRING(sso);

    cstring_t str1 = cstring_from(sso);
    cstring_t str2 = cstring_from(sso);

    expected_size = cstring_len(&str1) + cstring_len(&str2) + 1;

    cstring_append(&str1, &str2, 0, cstring_len(&str2));

    return EXIT_FAILURE;
}

static void oom_handler(size_t size)
{
    TEST_ASSERT(size == expected_size);

    exit(EXIT_SUCCESS);
}

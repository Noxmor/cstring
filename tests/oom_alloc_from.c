#include <stddef.h>
static void oom_handler(size_t size);

#define CSTRING_OOM_HANDLER(size) oom_handler(size)
#define CSTRING_ALLOC(size) NULL
#include "test.h"

int main()
{
    TEST_MAKE_STRING(heap, CSTRING_SSO_CAPACITY * 2);
    cstring_t str = cstring_from(heap);

    (void)str;

    return EXIT_FAILURE;
}

static void oom_handler(size_t size)
{
    TEST_ASSERT(size == CSTRING_SSO_CAPACITY * 2);

    exit(EXIT_SUCCESS);
}

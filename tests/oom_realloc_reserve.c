#include <stddef.h>
static void oom_handler(size_t size);

#define CSTRING_OOM_HANDLER(size) oom_handler(size)
#define CSTRING_REALLOC(ptr, size) NULL
#include "test.h"

static size_t expected_size;
static cstring_t str_state; // In order to keep asan happy

int main()
{
    TEST_MAKE_HEAP_STRING(heap);

    cstring_t str = cstring_from(heap);
    str_state = str;

    expected_size = cstring_capacity(&str) * 2;
    cstring_reserve(&str, expected_size);

    return EXIT_FAILURE;
}

static void oom_handler(size_t size)
{
    TEST_ASSERT(size == expected_size);

    exit(EXIT_SUCCESS);
}

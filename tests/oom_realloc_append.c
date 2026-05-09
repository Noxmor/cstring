#include <stddef.h>
static void oom_handler(size_t size);

#define CSTRING_OOM_HANDLER(size) oom_handler(size)
#define CSTRING_REALLOC(ptr, size) NULL
#include "test.h"

static size_t expected_size;
static cstring_t str1; // In order to keep asan happy

int main()
{
    TEST_MAKE_HEAP_STRING(heap);

    str1 = cstring_from(heap);
    cstring_t str2 = cstring_from(heap);

    expected_size = cstring_len(&str1) + cstring_len(&str2) + 1;

    cstring_append(&str1, &str2, 0, cstring_len(&str2));

    return EXIT_FAILURE;
}

static void oom_handler(size_t size)
{
    TEST_ASSERT(size == expected_size);

    exit(EXIT_SUCCESS);
}

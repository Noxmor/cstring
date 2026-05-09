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
    cstring_t heap_str = cstring_from(heap);

    TEST_ASSERT(!cstring_is_sso(&heap_str));

    cstring_t str = cstring_empty();
    cstring_reserve(&str, cstring_capacity(&heap_str) + 1);
    cstring_concat(&str, &heap_str);

    str_state = str;
    expected_size = cstring_capacity(&heap_str);
    cstring_shrink_to_fit(&str);

    return EXIT_FAILURE;
}

static void oom_handler(size_t size)
{
    TEST_ASSERT(size == expected_size);

    exit(EXIT_SUCCESS);
}

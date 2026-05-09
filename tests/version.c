#include "test.h"

#include <stdio.h>
#include <inttypes.h>

#define FORMAT ("%" PRIu16 ".%" PRIu8 ".%" PRIu8)

int main()
{
    const cstring_version_t v = CSTRING_VERSION;

    TEST_ASSERT(CSTRING_VERSION_MAJOR_OF(v) == CSTRING_VERSION_MAJOR);
    TEST_ASSERT(CSTRING_VERSION_MINOR_OF(v) == CSTRING_VERSION_MINOR);
    TEST_ASSERT(CSTRING_VERSION_PATCH_OF(v) == CSTRING_VERSION_PATCH);

    const cstring_version_t v2 = CSTRING_VERSION_MAKE(CSTRING_VERSION_MAJOR,
                                                      CSTRING_VERSION_MINOR,
                                                      CSTRING_VERSION_PATCH);

    TEST_ASSERT(v == v2);

    const size_t len = snprintf(NULL, 0, FORMAT, CSTRING_VERSION_MAJOR,
                                                 CSTRING_VERSION_MINOR,
                                                 CSTRING_VERSION_PATCH);

    char buffer[len + 1];
    sprintf(buffer, FORMAT, CSTRING_VERSION_MAJOR,
                            CSTRING_VERSION_MINOR,
                            CSTRING_VERSION_PATCH);

    TEST_ASSERT(strcmp(buffer, CSTRING_VERSION_STRING) == 0);

    return EXIT_SUCCESS;
}

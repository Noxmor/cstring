#ifndef CSTRING_H
#define CSTRING_H

#include <stddef.h>
#include <stdint.h>

// ##################
// ### PUBLIC API ###
// ##################

// +---------------+
// | HELPER MACROS |
// +---------------+

#define __CSTRING_STRINGIFY_IMPL(x) #x
#define __CSTRING_STRINGIFY(x) __CSTRING_STRINGIFY_IMPL(x)

#define __CSTRING_VERSION_MAJOR_SHIFT 16
#define __CSTRING_VERSION_MINOR_SHIFT 8
#define __CSTRING_VERSION_PATCH_SHIFT 0

#define __CSTRING_VERSION_MAJOR_MASK 0xFFFF
#define __CSTRING_VERSION_MINOR_MASK 0xFF
#define __CSTRING_VERSION_PATCH_MASK 0xFF

// +------------+
// | VERSIONING |
// +------------+

typedef uint32_t cstring_version_t;

#define CSTRING_VERSION_MAJOR 0
#define CSTRING_VERSION_MINOR 0
#define CSTRING_VERSION_PATCH 0

#define CSTRING_VERSION_MAKE(major, minor, patch) \
    (((cstring_version_t) (major) << __CSTRING_VERSION_MAJOR_SHIFT) | \
     ((cstring_version_t) (minor) << __CSTRING_VERSION_MINOR_SHIFT) | \
     ((cstring_version_t) (patch) << __CSTRING_VERSION_PATCH_SHIFT))

#define CSTRING_VERSION_MAJOR_OF(v) \
    (((v) >> __CSTRING_VERSION_MAJOR_SHIFT) & __CSTRING_VERSION_MAJOR_MASK)

#define CSTRING_VERSION_MINOR_OF(v) \
    (((v) >> __CSTRING_VERSION_MINOR_SHIFT) & __CSTRING_VERSION_MINOR_MASK)

#define CSTRING_VERSION_PATCH_OF(v) \
    (((v) >> __CSTRING_VERSION_PATCH_SHIFT) & __CSTRING_VERSION_PATCH_MASK)

#define CSTRING_VERSION \
    CSTRING_VERSION_MAKE(CSTRING_VERSION_MAJOR, \
                         CSTRING_VERSION_MINOR, \
                         CSTRING_VERSION_PATCH)

#define CSTRING_VERSION_STRING \
    (__CSTRING_STRINGIFY(CSTRING_VERSION_MAJOR) "." \
     __CSTRING_STRINGIFY(CSTRING_VERSION_MINOR) "." \
     __CSTRING_STRINGIFY(CSTRING_VERSION_PATCH))

// +-----------------+
// | CUSTOM HANDLERS |
// +-----------------+

#ifndef CSTRING_ALLOC
#include <stdlib.h>
#define CSTRING_ALLOC(size) malloc(size)
#endif

#ifndef CSTRING_REALLOC
#include <stdlib.h>
#define CSTRING_REALLOC(ptr, size) realloc(ptr, size)
#endif

#ifndef CSTRING_FREE
#include <stdlib.h>
#define CSTRING_FREE(ptr) free(ptr)
#endif

#ifndef CSTRING_OOM_HANDLER
#include <stdlib.h>
#define CSTRING_OOM_HANDLER(size) abort()
#endif

// +--------+
// | STRING |
// +--------+

#ifndef CSTRING_SSO_CAPACITY
#define CSTRING_SSO_CAPACITY sizeof(char*)
#endif

typedef struct cstring
{
    size_t len;
    size_t capacity;

    union
    {
        char* heap;
        char sso[CSTRING_SSO_CAPACITY];
    } data;
} cstring_t;

// +----------------------------+
// | CONSTRUCTION / DESTRUCTION |
// +----------------------------+

cstring_t cstring_empty(void);

cstring_t cstring_from(const char* str);

#ifdef CSTRING_IMPLEMENTATION

// ######################
// ### IMPLEMENTATION ###
// ######################

#include <stdlib.h>
#include <string.h>

// +----------------------------+
// | CONSTRUCTION / DESTRUCTION |
// +----------------------------+

cstring_t cstring_empty(void)
{
    cstring_t str = {0};
    str.capacity = CSTRING_SSO_CAPACITY;

    return str;
}

cstring_t cstring_from(const char* str)
{
    cstring_t s = cstring_empty();

    s.len = strlen(str);
    if (s.len + 1 > CSTRING_SSO_CAPACITY)
    {
        s.capacity = s.len + 1;
        const size_t size = sizeof(char) * s.capacity;
        s.data.heap = CSTRING_ALLOC(size);

        if (!s.data.heap)
        {
            CSTRING_OOM_HANDLER(size);
        }

        memcpy(s.data.heap, str, s.capacity);
    }
    else
    {
        memcpy(s.data.sso, str, s.len + 1);
    }

    return s;
}

#endif

#endif

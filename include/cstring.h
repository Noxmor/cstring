// Copyright (c) 2026 Noxmor

#ifndef CSTRING_H
#define CSTRING_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

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

#define CSTRING_NOT_FOUND SIZE_MAX

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

cstring_t cstring_copy(const cstring_t* str);

void cstring_free(cstring_t* str);

// +------------+
// | PROPERTIES |
// +------------+

size_t cstring_len(const cstring_t* str);

size_t cstring_capacity(const cstring_t* str);

bool cstring_is_sso(const cstring_t* str);

// +--------+
// | ACCESS |
// +--------+

const char* cstring_cstr(const cstring_t* str);

char cstring_at(const cstring_t* str, size_t idx);

// +---------------------+
// | STRING MANIPULATION |
// +---------------------+

void cstring_append(cstring_t* dst, const cstring_t* src, size_t idx, size_t len);

void cstring_concat(cstring_t* dst, const cstring_t* src);

void cstring_set(cstring_t* str, char c, size_t idx);

// +------------+
// | COMPARISON |
// +------------+

int cstring_compare(const cstring_t* str1, const cstring_t* str2);

bool cstring_equals(const cstring_t* str1, const cstring_t* str2);

// +--------+
// | SEARCH |
// +--------+

size_t cstring_find_char(const cstring_t* str, char c);

// +------------+
// | SUBSTRINGS |
// +------------+

cstring_t cstring_substring(const cstring_t* str, size_t idx, size_t len);

// +-----------------+
// | CASE CONVERSION |
// +-----------------+

void cstring_to_lower(cstring_t* str);

void cstring_to_upper(cstring_t* str);

// +--------+
// | MEMORY |
// +--------+

void cstring_reserve(cstring_t* str, size_t capacity);

void cstring_shrink_to_fit(cstring_t* str);

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

cstring_t cstring_copy(const cstring_t* str)
{
    return cstring_from(cstring_cstr(str));
}

void cstring_free(cstring_t* str)
{
    if (!cstring_is_sso(str))
    {
        CSTRING_FREE(str->data.heap);
    }

    *str = cstring_empty();
}

// +------------+
// | PROPERTIES |
// +------------+

size_t cstring_len(const cstring_t* str)
{
    return str->len;
}

size_t cstring_capacity(const cstring_t* str)
{
    return str->capacity;
}

bool cstring_is_sso(const cstring_t* str)
{
    return str->capacity <= CSTRING_SSO_CAPACITY;
}

// +--------+
// | ACCESS |
// +--------+

const char* cstring_cstr(const cstring_t* str)
{
    if (cstring_is_sso(str))
    {
        return str->data.sso;
    }

    return str->data.heap;
}

char cstring_at(const cstring_t* str, size_t idx)
{
    if (cstring_is_sso(str))
    {
        return str->data.sso[idx];
    }

    return str->data.heap[idx];
}

// +---------------------+
// | STRING MANIPULATION |
// +---------------------+

void cstring_append(cstring_t* dst, const cstring_t* src, size_t idx, size_t len)
{
    const size_t required_capacity = dst->len + len + 1;

    const char* src_buf = cstring_cstr(src) + idx;

    if (cstring_is_sso(dst))
    {
        if (required_capacity > CSTRING_SSO_CAPACITY)
        {
            const size_t size = sizeof(char) * required_capacity;
            char* heap = CSTRING_ALLOC(size);

            if (!heap)
            {
                CSTRING_OOM_HANDLER(size);
            }

            memcpy(heap, dst->data.sso, dst->len);
            memcpy(heap + dst->len, src_buf, len);
            dst->data.heap = heap;
            dst->capacity = required_capacity;
            dst->len += len;
            dst->data.heap[dst->len] = '\0';
        }
        else
        {
            memcpy(dst->data.sso + dst->len, src_buf, len);
            dst->len += len;
            dst->data.sso[dst->len] = '\0';
        }
    }
    else
    {
        if (required_capacity > dst->capacity)
        {
            const size_t size = sizeof(char) * required_capacity;
            dst->capacity = required_capacity;
            dst->data.heap = CSTRING_REALLOC(dst->data.heap, size);

            if (!dst->data.heap)
            {
                CSTRING_OOM_HANDLER(size);
            }
        }

        memcpy(dst->data.heap + dst->len, src_buf, len);
        dst->len += len;
        dst->data.heap[dst->len] = '\0';
    }

}

void cstring_concat(cstring_t* dst, const cstring_t* src)
{
    cstring_append(dst, src, 0, cstring_len(src));
}

void cstring_set(cstring_t* str, char c, size_t idx)
{
    if (idx >= str->len)
    {
        return;
    }

    if (cstring_is_sso(str))
    {
        str->data.sso[idx] = c;
    }
    else
    {
        str->data.heap[idx] = c;
    }
}

// +------------+
// | COMPARISON |
// +------------+

int cstring_compare(const cstring_t* str1, const cstring_t* str2)
{
    for (size_t i = 0; i < str1->len; ++i)
    {
        char char1 = cstring_at(str1, i);
        char char2 = cstring_at(str2, i);
        if (char1 != char2)
        {
            return char1 - char2;
        }
    }

    return cstring_at(str1, str1->len) - cstring_at(str2, str2->len);
}

bool cstring_equals(const cstring_t* str1, const cstring_t* str2)
{
    return cstring_compare(str1, str2) == 0;
}

// +--------+
// | SEARCH |
// +--------+

size_t cstring_find_char(const cstring_t* str, char c)
{
    const char* buf = cstring_cstr(str);

    for (size_t i = 0; i < str->len; ++i)
    {
        if (buf[i] == c)
        {
            return i;
        }
    }

    return CSTRING_NOT_FOUND;
}

// +------------+
// | SUBSTRINGS |
// +------------+

cstring_t cstring_substring(const cstring_t* str, size_t idx, size_t len)
{
    cstring_t substr = cstring_empty();

    cstring_append(&substr, str, idx, len);

    return substr;
}

// +-----------------+
// | CASE CONVERSION |
// +-----------------+

void cstring_to_lower(cstring_t* str)
{
    for (size_t i = 0; i < str->len; ++i)
    {
        const char c = cstring_at(str, i);

        if (c >= 'A' && c <= 'Z')
        {
            cstring_set(str, c + ('a' - 'A'), i);
        }
    }
}

void cstring_to_upper(cstring_t* str)
{
    for (size_t i = 0; i < str->len; ++i)
    {
        const char c = cstring_at(str, i);

        if (c >= 'a' && c <= 'z')
        {
            cstring_set(str, c - ('a' - 'A'), i);
        }
    }
}

// +--------+
// | MEMORY |
// +--------+

void cstring_reserve(cstring_t* str, size_t capacity)
{
    if (cstring_is_sso(str))
    {
        if (capacity > CSTRING_SSO_CAPACITY)
        {
            const size_t size = sizeof(char) * capacity;
            char* heap = CSTRING_ALLOC(size);

            if (!heap)
            {
                CSTRING_OOM_HANDLER(size);
            }

            memcpy(heap, str->data.sso, str->len + 1);

            str->data.heap = heap;
            str->capacity = capacity;
        }
    }
    else
    {
        if (capacity > str->capacity)
        {
            const size_t size = sizeof(char) * capacity;
            str->capacity = capacity;
            str->data.heap = CSTRING_REALLOC(str->data.heap, size);

            if (!str->data.heap)
            {
                CSTRING_OOM_HANDLER(size);
            }
        }
    }
}

void cstring_shrink_to_fit(cstring_t* str)
{
    if (cstring_is_sso(str))
    {
        return;
    }

    if (str->len < CSTRING_SSO_CAPACITY)
    {
        char* heap = str->data.heap;
        memcpy(str->data.sso, heap, str->len + 1);
        str->capacity = CSTRING_SSO_CAPACITY;
        free(heap);
    }
    else if (str->capacity > str->len + 1)
    {
        const size_t capacity = sizeof(char) * (str->len + 1);
        str->data.heap = CSTRING_REALLOC(str->data.heap, capacity);
        str->capacity = capacity;

        if (!str->data.heap)
        {
            CSTRING_OOM_HANDLER(capacity);
        }
    }
}

#endif

#endif

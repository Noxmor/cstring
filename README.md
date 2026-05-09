# cstring
Single-header string library written in C99

***

> [!WARNING]
This library is still in early development.

## Installation
You can either copy `include/cstring.h` directly into your project or install
`cstring.h` on your system via `make install`, which will allow you to do the
following:
```c
#include <cstring.h>
```

## Usage
Since `cstring.h` is a `single-header library` where the implementation details
reside in the same file, you will have to exactly **once** define the
`CSTRING_IMPLEMENTATION` macro **before** including `cstring.h` in exactly
**one** translation unit.

### Example
```c
// cstring.c
#define CSTRING_IMPLEMENTATION
#include <cstring.h>
```

***

## Configuration
`cstring.h` is customizable to an extent via certain macros that will only use
their default implementation if you don't provide a custom implementation before
including `cstring.h`.

### Small string optimization (SSO) capacity
Instead of **always** allocating memory dynamically for each and every string,
small strings are stored directly inside the `cstring_t` struct. By default,
this does not increase the size of the `cstring_t` struct itself, since only the
space that would otherwise be needed for storing a dynamically allocated string
will be used for storing small strings. However, you can decide to be able to
store larger strings directly inside the `cstring_t` struct with the tradeoff of
the struct becoming larger. You can do this by defining the
`CSTRING_SSO_CAPACITY` macro with your desired capacity before including
`cstring.h`.

### Custom allocators
By default, `cstring.h` will use `malloc`, `realloc` and `free` for dynamic
allocations. If you want to instead have `cstring.h` use your own custom
allocator, define the `CSTRING_ALLOC`, `CSTRING_REALLOC` and `CSTRING_FREE`
macros before including `cstring.h`. These macros **must** match the function
signatures of the `malloc`, `realloc` and `free` functions respectively.

### Out-of-memory (OOM) handlers
By default, `cstring.h` will call the `abort` function whenever a dynamic
allocation failed. If you want to instead have `cstring.h` call your custom
handler function, define the `CSTRING_OOM_HANDLER` macro before including
`cstring.h`. This macro has exactly **one** parameter `size` of type `size_t`
for the size of the failed allocation.
> [!NOTE]
Since your custom handler will only be called when a dynamic allocation failed,
letting your custom handler return to the function inside `cstring.h` will lead
to **undefined behaviour** (UB) and will at best crash your program. Therefore,
custom OOM handler functions should always terminate the program.

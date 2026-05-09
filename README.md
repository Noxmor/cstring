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

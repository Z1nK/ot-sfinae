# ot-sfinae

Template-based C++ implementation of `print_ip` using SFINAE and type traits.

## Overview

This project demonstrates compile-time selection of `print_ip` overloads for:

- integral types (printed as dotted bytes)
- floating-point types
- string-like types
- container types
- tuples with homogeneous element types

## Files

- `src/main.hpp` - core templates, traits, and overloads
- `src/main.cpp` - usage examples / entry point

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Generate Documentation

```bash
doxygen Doxyfile
```

Generated HTML docs are available at `doc/html/index.html`.

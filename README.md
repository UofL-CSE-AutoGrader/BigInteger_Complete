# BigInteger

A C++17 arbitrary-precision integer library.The implementation stores values as
32-bit limbs and supports signed integer arithmetic, comparisons, bitwise
operations, modular arithmetic, and mixed operations with built-in integral
types.

## Use this repository as a CMake FetchContent dependency

In another CMake project, paste this into that project's `CMakeLists.txt`.
The important values are the repository URL and tag:

```cmake
include(FetchContent)

FetchContent_Declare(
    BigInteger
    GIT_REPOSITORY https://github.com/UofL-CSE-AutoGrader/BigInteger_Complete.git
    GIT_TAG v2.0.0
)

FetchContent_MakeAvailable(BigInteger)

target_link_libraries(your_target PRIVATE BigInteger::BigInteger)
```




## Features

- Construct `Integer` values from `int64_t` values or decimal strings.
- Convert values back to decimal text with `toString()` or stream them with
  `operator<<`.
- Use normal arithmetic operators: `+`, `-`, `*`, `/`, `%`, unary `-`, `++`,
  and `--`.
- Use assignment operators: `+=`, `-=`, `*=`, `/=`, `%=`.
- Compare values with `==`, `!=`, `<`, `<=`, `>`, and `>=`.
- Use bitwise operators for non-negative integer-style values: `&`, `|`, `^`,
  `~`, `<<`, and `>>`.
- Use number-theory helpers including `abs()`, `gcd()`, `lcm()`, `power()`,
  `power_mod()`, and `mod_inverse()`.
- Mix `Integer` values with built-in integral types in arithmetic, comparison,
  and bitwise expressions.



## Requirements

- CMake 3.14 or newer
- A C++17-compatible compiler
- Network access when fetching this project or when building this project's
  tests, because tests fetch GoogleTest with `FetchContent`

## Build

From the repository root:

```sh
cmake -S . -B build
cmake --build build
```

This builds:

- `integer_lib`: the library target
- `integer_main`: a small executable that demonstrates common operations
- `integer_tests`: the GoogleTest test executable

## Run tests

```sh
ctest --test-dir build --output-on-failure
```

You can also run the test binary directly:

```sh
./build/integer_tests
```

## Run the demo

```sh
./build/integer_main
```

The demo constructs large integers, performs arithmetic, computes GCD/LCM,
tests modular inverse, and compares regular exponentiation with modular
exponentiation.

## Basic usage

```cpp
#include "Integer.hpp"
#include <iostream>

int main() {
    Integer a("123456789012345678901234567890");
    Integer b(42);

    Integer sum = a + b;
    Integer product = a * b;
    Integer remainder = a % Integer(97);

    std::cout << "sum = " << sum << '\n';
    std::cout << "product = " << product << '\n';
    std::cout << "remainder = " << remainder.toString() << '\n';
}
```

## Using the CMake target

When this repository is added as part of another CMake project, link against the
provided `BigInteger::BigInteger` alias target:

```cmake
add_subdirectory(path/to/BigInteger_Complete)
target_link_libraries(your_target PRIVATE BigInteger::BigInteger)
```

Then include the public header in your C++ code:

```cpp
#include "Integer.hpp"
```

## API overview

### Construction and output

```cpp
Integer zero;
Integer small(-123456789);
Integer large("987654321098765432109876543210");

std::string text = large.toString();
std::cout << large << '\n';
```

Decimal string construction accepts optional leading `-` and ignores leading
zeroes. Invalid characters throw `std::invalid_argument`.

### Arithmetic and comparison

```cpp
Integer a("100000000000000000000");
Integer b(3);

Integer q = a / b;
Integer r = a % b;

if (q > r) {
    q += 1;
}
```

Division or modulo by zero throws `std::invalid_argument`.

### Mixed integral operations

`Integer_Mixed_Ops.hpp` is included by `Integer.hpp`, so expressions with
built-in integral types work on either side of most operators:

```cpp
Integer x(1000);

Integer y = x + 500;
Integer z = 3 * x - 1;
bool ok = -1000 < x;
```

### Number-theory helpers

```cpp
Integer a("4855234577788899234509871023409817234098172350987690227473");
Integer m("44854567892341234123409850987908709869876123409812734987654321113893929239484");

Integer g = Integer::gcd(Integer(48), Integer(18));
Integer l = Integer::lcm(Integer(21), Integer(6));
Integer inv = Integer::mod_inverse(a, m);
Integer pow = a.power(Integer(12));
Integer mod_pow = a.power_mod(Integer(12), m);
```

Notes:

- `power()` and `power_mod()` require non-negative exponents.
- `power_mod()` requires a non-zero modulus.
- `mod_inverse()` requires a positive non-zero modulus and relatively prime
  inputs.
- `gcd()` is defined for non-negative inputs in this implementation.

### Bitwise operations

```cpp
Integer mask(0b1100);
Integer value(0b101010);

Integer both = value & mask;
Integer either = value | mask;
Integer shifted = value << 4;
```

Negative bit indexes throw `std::invalid_argument`. Bitwise NOT is not defined
for negative `Integer` values.

## Notes for assignment use

The public class is intentionally named `Integer` and lives in the global
namespace so it can be included directly by dependent assignments. Include
`Integer.hpp`, link the CMake library target, and use `Integer` as a drop-in
arbitrary-precision integer type where the assignment requires it.

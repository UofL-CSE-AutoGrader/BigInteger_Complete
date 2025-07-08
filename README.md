# Assignment: Arbitrary-Precision Integers - Scaling Up Your Skills

## 🧙 Epic Story

Modern programming languages like Python allow developers to work with arbitrarily large integers without worrying about overflow. In lower-level languages like C and C++, libraries such as GMP provide similar functionality, enabling high-precision arithmetic beyond the limits of primitive types. These capabilities are essential in fields like cryptography and combinatorics, where extremely large numbers are common.

As a computer science student, it’s important to understand how these capabilities are achieved. This assignment challenges you to implement an Integer class that mimics the behavior of built-in integer types while supporting values far beyond native limitations, using a dotted-base-2³² internal representation.

Your task is to build a fully functional Integer class that supports:

* Mixed-type arithmetic (between Integer and primitive types)
* Comparison operators
* Modular arithmetic
* Bit-level operations
* Stream-friendly I/O

The goal is to produce a modular `Integer` class whose behavior mirrors arithmetic with primitive language integers (e.g. `int`). Any developer using your class should be able to swap the primitive `int` for `Integer` with little to no other changes. 

---

## 🛠 Project Manager Statement

As your C++ instructor, I need to evaluate your ability to:

* Model numerical abstractions using class-based design
* Overload operators efficiently in a way that matches native type semantics
* Handle bitwise and modular operations on arbitrary sized numbers
* Write modular, maintainable, and testable C++ code
* Implement type safety tools provided by modern C++ standards for propagating templates
* Implement stream-friendly output instead of making calls to `toString()` methods

Your deliverable must satisfy the Acceptance Criteria below to be considered complete.

---

## ✅ Acceptance Criteria

In order to receive full credit for this assignment, you must meet *all* of the following criteria:

* Implement the `Integer` class defined in `include/Integer.hpp` using modular `.cpp` files.
* Represent arbitrarily large signed integers using a `std::vector<uint32_t>` with base 2³² limbs.
* Implement the following:

  * Constructors for `int64_t` and base-10 `std::string` parameters
  * YOU CANNOT **INCLUDE** (or use) any libraries other than the ones already provided on the `.hpp` and `.cpp` files.
  * YOU CANNOT change the `Integer.hpp` file.
  * You CANNOT alter then workflow `autograder.yaml` file. 
  * All the files and directories have been created for you.  You do not need to create any new files or directories.
  * You should not edit the files in the `tests` directory.
  * Arithmetic operators: `+`, `-`, `*`, `/`, `%`
  * Bitwise operators: `&`, `|`, `^`, `~`, `<<`, `>>`
  * Increment/decrement (prefix and postfix)
  * Unary negation
  * Comparison operators: `==`, `!=`, `<`, `<=`, `>`, `>=`
  * Compound assignment (`+=`, `-=`, etc.) for all the arithmetic and bitwise operators mentioned above.
  * Errors should be `thrown` for certain conditions. Analyze the unit test files and find the types of errors your class should throw.
* Implement utility methods:

  * `abs()` – returns the absolute value
  * `normalize()` – ensures internal representation has no leading zeros
  * `setBit(int)`, `getBit(int)` – for accessing/modifying individual bits
  * `gcd(Integer a, Integer b)` - Calculate the GCD of two large integers
  * `lcm(Integer a, Integer b)` - Calculatte the LCM of two large integers
* Implement modular arithmetic:
  * `power()` – exponentiation using successive squaring
  * `power_mod()` – modular exponentiation
  * `mod_inverse()` – multiplicative inverse when `gcd(a, m) = 1`
* Overload the `<<` operator for output (printing strings using `cout`).
  **You must not rely on calling `toString()` directly to print values.**
* All operations should behave identically to native integers for valid values.
* Your implementation must pass all unit tests in the `tests/` directory.

A sample test case output is provided in [`main.cpp`](./src/main.cpp) for experimentation.  The output for a correct implementation can be found in the file `main_output.txt`.

---

## 🧮 Grading Criteria

This assignment is worth **100 points**, awarded based on milestone completion and verified automatically through GitHub Actions.

| Milestone                | Description                                                   | Points    |
| ------------------------ | ------------------------------------------------------------- | --------- |
| ✅ Assignment Accepted    | You clicked the GitHub Classroom invitation link              | 10 points |
| 📦 First Commit Pushed   | You pushed any code to your repository                        | 20 points |
| ✅✅ All Unit Tests Passed | GitHub Actions shows all unit tests passing (green checkmark) | 70 points |

> 🚫 **No partial credit will be awarded within categories.**

The autograder will reset any changes may to unit test files. If you modify the `autograder.yml` file you will be forced to restart the assignment (repository deleted). GitHub notifies the instructor and TA when the autograder file has been mutated. 

### Scoring Examples:

| Scenario                                               | Total Points |
| ------------------------------------------------------ | ------------ |
| Assignment not accepted                                | 0 points     |
| Assignment accepted, no commits                        | 10 points    |
| Assignment accepted, commits pushed                    | 30 points    |
| Assignment accepted, code pushed, and all tests passed | 100 points   |

---

**Build for scale. Test for correctness. Think like a compiler.**

A skilled developer will create the base line tools first then use those tools to create other tools.

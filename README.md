# Minimal-TI
A minimal constexpr C++17 type info library.

## Background
This project aims to provide a base for using "pretty function" reflection while preserving compile-time performance. With the header being only 100 LOC anyone can understand and modify the current code to their own needs.

## Features
* C++17
* Header Only
* Dependency-free
* Compile-time
* Uses std::string_view
* TypeId hashing FNV-1a
* Optimised for compile-time performance
* Supports structs, classes, enums & unions

## Library Interface
* `mti::GetName<T>()` Returns an `std::string_view` containing the name of T.
* `mti::GetHash<T>()` Returns an `std::size_t` hash of the name of T. (Hashing done using FNV-1a)
* `mti::GetTypeId<T>()` Returns an `mti::TypeId` structure with info of the type T.


## Examples
```C++
class MyClass {
    int y;
};
```
* Compile-time name checks
    ```C++
        static_assert(mti::GetName<int>() == "int");
        static_assert(mti::GetName<MyClass>() == "MyClass");
    ```
* Compile-time type hashing
    ```C++
        constexpr mti::TypeId type = mti::GetTypeId<MyClass>();
        constexpr std::size_t hash = mti::GetHash<MyClass>();
        static_assert(type.hash() == hash);
        static_assert(type.hash() != mti::GetHash<int>());
    ```
* Type Id functions example
    ```C++
        mti::TypeId type = mti::GetType<MyClass>();
        type.hash() == mti::GetHash<MyClass>(); // saved hash
        type.name() == mti::GetName<MyClass>(); // saved name (returns std::string_view directly to the executables data section)
        // Comparison operator O(1) compares the hashes calculated during compile-time
        bool same_type = type == mti::GetType<int>(); // False
    ```


## Using minimal-ti
Include the `minimal-ti.h` header found in the root of this repository.


## Compiler Support
All compilers need to be set in C++17 mode, as C++17 is required for std::string_view.

Compilers tested:

* GCC >= 7.3
* Clang >= 5.0.0
* MSVC >= 19.14 (VS 2017 version 15.7)

_Note: If you are compiling in 32-bit mode you need to convert the FNV-1a hashing from 64bit to 32bit._

## Known Limitations
There is a difference in the result between between GCC & Clang vs MSVC when requesting a name of a templated type with a non fundamental type as template parameter.
Consider the following:
```C++
class MyClass{
};

template<typename T>
struct Templated{
};
```

In GCC and Clang the following will compile as expected:
```C++
static_assert(mti::GetName<Templated<MyClass>() == "Templated<MyClass>")
```
In MSVC the result of `mti::GetName<Templated<MyClass>>()` would be:
```C++
"Templated<class MyClass>"
```
Beware of this limitiation if you intend to run runtime comparisons with binaries built from different compilers.


## Licensed under the [MIT License](LICENSE)
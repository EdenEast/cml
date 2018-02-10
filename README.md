# Cml

[![Build Status](https://travis-ci.org/CruizeMissile/cml.svg)](https://travis-ci.org/CruizeMissile/cml)
[![Build status](https://ci.appveyor.com/api/projects/status/qpm5fthqwws3xe98?svg=true)](https://ci.appveyor.com/project/CruizeMissile/cml)

> Constexpr Math Library, focusing on graphics and physics math.

# Ideas of this library

- A vector is a typedef for a matrix. The matrix has one component that is 1.
- The matrix class is constexpr compatible
- Cml functions are also constexpr compatible and able to be used at compile time
- There are useful type defines for most common cases.

# Example usage

```cpp
#include "cml/cml.hpp"

void foo()
{
    cml::matrix<3, 3, int32_t> identity_mat(1, 0, 0, 0, 1, 0, 0, 0, 1);
    
    // can be also initialized by passing vectors. Note that there are already useful
    // defines for common use cases. For the complete list of defineds see "cml/definitions.hpp"
    identity_mat = cml::imat3(cml::ivec3(1, 0, 0), cml::ivec3(0, 1, 0), cml::ivec3(0, 0, 1));
    assert(identity_mat == cml::imat3::identity());

    // A vector is just a matrix with one axis set to 1
    static_assert(cml::vec3(1.f, 2.f, 3.f) == cml::matrix<3, 1, float>(1.f, 2.f, 3.f));

    // You can access a value from a vector at compile time
    static_assert(cml::ivec4(1, 2, 3, 4)._<'z'>() == 3);

    // You can even create another vector from the components of the other
    cml::ivec2 value = cml::ivec4(1, 2, 3, 4)._<'xw'>();
    assert(value == cml::ivec2(1, 4));

    // Vector components can also be accessed from their components. This works up to vector 4
    // you can use one of either: xyzw, rgba, stuv 
    auto vx = value.x;
    assert(vx == value.r);
    assert(vx == value.s);

    // for matrix you can access values from the its components or the row vectors that make it up
    assert(1 == identity_mat.components[4]);
    assert(cml::ivec3(0, 1, 0).components == identity_mat.rows[1].components);
}
```

There are also lots of functions that are implemented. You can find them under "cml/functions".

# Compiler support

Cml is a header only library requiring the latest and greatest features of c++17. Cml has a minimum requirement
for compilers of:

- gcc 7.1+
- clang 4.0+
- msvc 15.3+

# Building and installing with CMake

Cml is a header only library and is designed to be included as a submodule into your project
```bash
mkdir external
git submodule add https://github.com/cruizemissile/cml external/cml
```

Now add cml as a target include directory. If you are using CMake this can easily be done.

```cmake
cmake_minimum_version(VERSION 3.1)

# ...

add_subdirectory(external/cml)

add_executable(foo)
target_link_library(foo libcml)
```

# Development

Cml is still under development and is not fully feature complete.

[cml]: https://githuib.com/cruizemissile/cml

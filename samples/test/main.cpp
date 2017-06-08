
#include <cml/cml.hpp>

int main()
{
    static_assert(static_cast<cml::ivec4>(cml::cvec4('\x04', 3, 2, 1))._<'x'>() == 4);
    static_assert(static_cast<cml::ivec4>(cml::ivec4(4, 3, 2, 1))._<'y'>() == 3);
    static_assert(static_cast<cml::dvec4>(cml::ivec4(4, 3, 2, 1))._<'z'>() == 2);
//     static_assert(static_cast<cml::cvec4>(cml::ivec4(4, 3, 2, 1))._<'w'>() == 1); // must static assert
    static_assert(cml::cvec4(cml::ivec4(4, 3, 2, 1).unsafe_cast<uint8_t>())._<'w'>() == 1);

    static_assert(static_cast<uint32_t>(cml::cvec4(4, 3, 2, 1)) == 0x01020304); // only OK on little endians

    // eq / neq operators
    static_assert(cml::ivec4(4, 3, 2, 1) == cml::ivec4(4, 3, 2, 1));
    static_assert(!(cml::ivec4(4, 3, 2, 1) != cml::ivec4(4, 3, 2, 1)));
    static_assert((cml::ivec4(4, 3, 2, 1) != 0));
    static_assert((5 != cml::ivec4(4, 3, 2, 1)));
    static_assert(!(0 == cml::ivec4(4, 3, 2, 1)));
    static_assert(!(cml::ivec4(4, 3, 2, 1) == 1));

    // + -
    static_assert(cml::ivec4(1) + 1 == 2);
    static_assert(1 + cml::ivec4(1) == 2);
    static_assert(cml::ivec4(1) + 1 == cml::ivec4(2));
    static_assert(1 + cml::ivec4(1) == cml::ivec4(2));
    static_assert(cml::ivec4(1) - 1 == 0);
    static_assert(1 - cml::ivec4(1) == 0);
    static_assert(cml::ivec4(1) - 1 == cml::ivec4(0));
    static_assert(1 - cml::ivec4(1) == cml::ivec4(0));



    cml::vector<5, int> v(1, cml::ivec2(2, 3), 4, 5);
    v._<'xy'>()._<'x'>() += 5;

    return v._<'yx'>()._<'x'>();
}

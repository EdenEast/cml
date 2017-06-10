
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


    static_assert(cml::mat3::identity() == cml::mat3(cml::vec3(1, 0, 0),
                                                     cml::vec3(0, 1, 0),
                                                     cml::vec3(0, 0, 1)));


    static_assert(cml::mat<3, 2>{} * cml::mat<2, 3>{} == cml::mat<2, 2>{});
    static_assert(cml::mat<3, 2>{} * cml::mat<2, 3>{} == 0.0f);
    static_assert(cml::mat3::identity() * cml::mat3::identity() == cml::mat3::identity());

    static_assert(cml::ivec3{4, -5, -3} * cml::imat3::identity() == cml::ivec3{4, -5, -3});
    static_assert(cml::ivec3{4, -5, -3} * (2 * cml::imat3::identity()) == 2 * cml::ivec3{4, -5, -3});

    static_assert(cml::transpose(cml::ivec3{4, -5, -3}) * cml::ivec3{4, -5, -3} == cml::imat3(4 * cml::ivec3{4, -5, -3}, -5 * cml::ivec3{4, -5, -3}, -3 * cml::ivec3{4, -5, -3}));

    static_assert(cml::imat<3, 2>{2, 3, -1, 6, 1, -2} * cml::imat<2, 3>{4, -5, -3, 0, 1, 2} == cml::imat<2, 2>{-2, -12, 19, -34});


    constexpr cml::imat3 m{2, 3, -1, 6, 1, -2};
    cml::vector<7, int> v(m.rows[0].x, cml::ivec2(2, 3), m.rows[0]._<'xy'>(), 4, 5);
    v._<'xy'>()._<'x'>() += 5;
    v._<'xy'>()._<'x'>() += 5;
    v.x *= 1;

    return v._<'yx'>().x;
}

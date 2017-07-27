
#define CML_COMPILE_TEST_CASE 1
#include <cml/cml.hpp>
#include <math.h>

#define STRING(STR) #STR
#define CHECK(expr) if (!(expr)) {printf("Check failed: %s\n", STRING(expr));}


int main()
{
    static_assert(cml::ivec4(cml::ivec3(1, 6, 1), 6) == cml::ivec4(1, 6, 1, 6));

    static_assert(static_cast<cml::ivec4>(cml::cvec4(4, 3, 2, 1))._<'x'>() == 4);
    static_assert(static_cast<cml::ivec4>(cml::cvec4(4, 3, 2, 1)).components[0] == 4);
    static_assert(static_cast<cml::ivec4>(cml::cvec4(4, 3, 2, 1)).components[1] == 3);
    static_assert(static_cast<cml::ivec4>(cml::cvec4(4, 3, 2, 1)).components[2] == 2);
    static_assert(static_cast<cml::ivec4>(cml::cvec4(4, 3, 2, 1)).components[3] == 1);

    static_assert(static_cast<cml::ivec4>(cml::ivec4(4, 3, 2, 1))._<'y'>() == 3);
    static_assert(static_cast<cml::dvec4>(cml::uvec4(4, 3, 2, 1))._<'z'>() == 2);
//     static_assert(static_cast<cml::cvec4>(cml::ivec4(4, 3, 2, 1))._<'w'>() == 1); // must static assert
    static_assert(cml::cvec4(cml::ivec4(4, 3, 2, 1).unsafe_cast<int8_t>())._<'w'>() == 1);

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

    static_assert(cml::imat3::identity() == cml::imat3(cml::ivec3(1, 0, 0),
                                                       cml::ivec3(0, 1, 0),
                                                       cml::ivec3(0, 0, 1)));

    static_assert(cml::imat3::identity() == cml::imat3(1, 0, 0,
                                                       0, 1, 0,
                                                       0, 0, 1));


    static_assert(cml::mat<3, 2>{} * cml::mat<2, 3>{} == cml::mat<2, 2>{});
    static_assert(cml::mat<3, 2>{} * cml::mat<2, 3>{} == 0.0f);
    static_assert(cml::mat3::identity() * cml::mat3::identity() == cml::mat3::identity());

    static_assert(cml::ivec3{4, -5, -3} * cml::imat3::identity() == cml::ivec3{4, -5, -3});
    static_assert(cml::ivec3{4, -5, -3} * (2 * cml::imat3::identity()) == 2 * cml::ivec3{4, -5, -3});
    static_assert(cml::ivec3{4, -5, -3} * 2 == 2 * cml::ivec3{4, -5, -3});
    static_assert(cml::ivec3{4, -5, -3} * 2 == cml::ivec3{2 * 4, 2 * -5, 2 * -3});

    static_assert(cml::transpose(cml::ivec3{4, -5, -3}) * cml::ivec3{4, -5, -3} == cml::imat3(4 * cml::ivec3{4, -5, -3}, -5 * cml::ivec3{4, -5, -3}, -3 * cml::ivec3{4, -5, -3}));
    static_assert(cml::transpose(cml::ivec3{1, 1, 1}) * cml::ivec3{4, -5, -3} == cml::imat3(cml::ivec3{4, -5, -3}, cml::ivec3{4, -5, -3}, cml::ivec3{4, -5, -3}));

    static_assert(cml::imat<3, 2>{2, 3, -1, 6, 1, -2} * cml::imat<2, 3>{4, -5, -3, 0, 1, 2} == cml::imat<2, 2>{-2, -12, 19, -34});



    // fixed
    static_assert(cml::f88(2.5).data == 0x0280);
    static_assert(cml::f88(0.5).data == 0x0080);
    static_assert(cml::f88(2).data == 0x0200);
    static_assert(cml::f88(2.5).to<double>() == 2.5);
    static_assert(cml::f88(2.5).to<float>() == 2.5f);
    static_assert(cml::f88(2.5).to<int>() == 2);
    static_assert(cml::f88(-2.5).to<int>() == -2);
    static_assert(cml::f88(-2.5).to<double>() == -2.5);
    static_assert(cml::f88(-2).to<int>() == -2);
    static_assert(cml::f88(2.5).to<cml::f1616>() == cml::f1616(2.5));
    static_assert(static_cast<cml::f1616>(cml::f88(2.5)) == cml::f1616(2.5));
    static_assert(cml::f1616::from(cml::f88(2.5)) == cml::f1616(2.5));

    static_assert((cml::f88(-2) + cml::f88(2)) == cml::f88(0));
    static_assert((cml::f88(-2.5) + cml::f88(2.5)) == cml::f88(0));
    static_assert((cml::f88(-1.5) + cml::f88(2.5)) == cml::f88(1.0));
    static_assert((cml::f88(-1) - cml::f88(0.5) - cml::f88(2) - cml::f88(0.5)) == cml::f88(-4));

    static_assert((cml::f88(-1) * cml::f88(0.5)) == cml::f88(-0.5));
    static_assert((cml::f88(1) / cml::f88(2)) == cml::f88(0.5));
    static_assert((++cml::f88(1)) == cml::f88(2));
    static_assert((cml::f88(1)++) == cml::f88(2));
    static_assert((--cml::f88(1)) == cml::f88(0));
    static_assert((cml::f88(1)--) == cml::f88(0));
    static_assert((cml::f88(cml::f88(1))--) == cml::f88(0));

    static_assert((cml::f88vec2{2, 3}).components[0] == cml::f88(2));
    static_assert(cml::f88mat<3, 2>{2, 3, -1, 6, 1, -2} * cml::f88mat<2, 3>{4, -5, -3, 0, 1, 2} == cml::f88mat<2, 2>{-2, -12, 19, -34});

    static_assert((cml::f1616vec3(1, cml::f88vec2{2, 3})) == cml::f1616vec3{1, 2, 3});
    static_assert((cml::f88vec2{2, 3}).unsafe_cast<cml::f1616>() == cml::f1616vec2{2, 3});


    // runtime test

    // fixed points
    constexpr cml::f88mat3 m{0, 3, -1, 6, 1, -2};
    cml::vector<7, cml::f1616> v(m.rows[0].x, cml::ivec2(2, 3), m.rows[0]._<'xy'>(), 4, 5);
    v._<'xy'>() += cml::f0824(5);
    v._<'zw'>() = v._<'xy'>() + cml::f88(5);
    v._<'yy'>() *= cml::f1616(5);

    constexpr cml::mat3 im{0, 3, -1, 6, 1, -2};
    cml::vector<7, int32_t> iv(m.rows[0].x, cml::ivec2(2, 3), m.rows[0]._<'xy'>(), 4, 5);
    iv._<'xy'>() += 5;
    iv._<'zw'>() = iv._<'xy'>() + 5;
    iv._<'yy'>() *= 5;

    printf("iv.x %i, v.x %i (must be 175 both)\n", int(iv._<'yx'>().x), cml::ivec2(v._<'yx'>().unsafe_cast<int32_t>()).x);

    CHECK(cml::is_equal(cml::sqrt(5.0), std::sqrt(5.0)));
    CHECK(cml::sqrt(5.0f) == std::sqrt(5.0f));
    
    CHECK(std::sqrt(5.0) == cml::sqrt(5.0));
    CHECK(std::sqrt(5.f) == cml::sqrt(5.f));

    // should return 175
    return cml::ivec2(v._<'yx'>().unsafe_cast<int32_t>()).x;
}

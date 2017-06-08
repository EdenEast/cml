
#include <cml/cml.hpp>

int main()
{
    static_assert(static_cast<cml::implementation::vector<4, int>>(cml::implementation::vector<4, char>('\x04', 3, 2, 1)).at<'x'>() == 4);
    static_assert(static_cast<cml::implementation::vector<4, int>>(cml::implementation::vector<4, int>(4, 3, 2, 1)).at<'y'>() == 3);
    static_assert(static_cast<cml::implementation::vector<4, double>>(cml::implementation::vector<4, int>(4, 3, 2, 1)).at<'z'>() == 2);
//     static_assert(static_cast<cml::implementation::vector<4, char>>(cml::implementation::vector<4, int>(4, 3, 2, 1)).at<'w'>() == 1); // must static assert
    static_assert(cml::implementation::vector<4, char>(cml::implementation::vector<4, int>(4, 3, 2, 1).unsafe_cast<char>()).at<'w'>() == 1);

    static_assert(static_cast<int>(cml::implementation::vector<4, char>(4, 3, 2, 1)) == 0x01020304); // only OK on little endians

    // eq / neq operators
    static_assert(cml::implementation::vector<4, int>(4, 3, 2, 1) == cml::implementation::vector<4, int>(4, 3, 2, 1));
    static_assert(!(cml::implementation::vector<4, int>(4, 3, 2, 1) != cml::implementation::vector<4, int>(4, 3, 2, 1)));
    static_assert((cml::implementation::vector<4, int>(4, 3, 2, 1) != 0));
    static_assert((5 != cml::implementation::vector<4, int>(4, 3, 2, 1)));
    static_assert(!(0 == cml::implementation::vector<4, int>(4, 3, 2, 1)));
    static_assert(!(cml::implementation::vector<4, int>(4, 3, 2, 1) == 1));

    // + -
    static_assert(cml::implementation::vector<4, int>(1) + 1 == 2);
    static_assert(1 + cml::implementation::vector<4, int>(1) == 2);
    static_assert(cml::implementation::vector<4, int>(1) + 1 == cml::implementation::vector<4, int>(2));
    static_assert(1 + cml::implementation::vector<4, int>(1) == cml::implementation::vector<4, int>(2));
    static_assert(cml::implementation::vector<4, int>(1) - 1 == 0);
    static_assert(1 - cml::implementation::vector<4, int>(1) == 0);
    static_assert(cml::implementation::vector<4, int>(1) - 1 == cml::implementation::vector<4, int>(0));
    static_assert(1 - cml::implementation::vector<4, int>(1) == cml::implementation::vector<4, int>(0));




    cml::implementation::vector<5, int> v(1, cml::implementation::vector<2, int>(2, 3), 4, 5);
    v.at<'xy'>().at<'x'>() += 5;

    return v.at<'yx'>().at<'x'>();
}

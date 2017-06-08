
#include <cml/cml.hpp>

int main()
{
    cml::implementation::vector<5, int> v(1, cml::implementation::vector<2, int>(2, 3), 4, 5);
    v.at<'xy'>() = 5;
    return v.at<'yx'>().at<'x'>();
}

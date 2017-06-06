
#include <cml/cml.hpp>

int main()
{
    cml::implementation::vector<5, int> v;
    v.at<'xy'>() = 5;
    return v.at<'yx'>().at<'x'>();
}

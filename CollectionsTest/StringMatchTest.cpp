#include <random>
#include <gtest/gtest.h>
#include "../Collections/StringPatternMatch/StringPM.h"

class String_match_test : public testing::Test
{
public:
    std::uniform_int_distribution<int> dist;
    std::default_random_engine e;

    String_match_test()
    {
        // 伪随机数生成器
        // 以随机值播种，若可能
        std::random_device r;
        // 选择 1 与 10000 间的随机数
        std::default_random_engine e1(r());
        e = e1;
        std::uniform_int_distribution<int> uniform_dist(1, 10000);
        dist = uniform_dist;
    }
};


TEST_F(String_match_test, brute_force_match)
{
    std::string patter = "abcd";
    std::string text = "aaaaaabcdaaaaaaaaaaaadsd";
    int positon = StringPM::brute_force_match(patter.c_str(), text.c_str());
    ASSERT_EQ(5, positon);
}

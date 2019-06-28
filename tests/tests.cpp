#include <iostream>
#include <exception>
#include "turbo_coder.h"
#include <gtest/gtest.h>

template <class T>
bool CompareVector(const std::vector<T>& kV_0, const std::vector<T>& kV_1)
{
    if (kV_0.size() != kV_1.size()) return 0;
    for (size_t it = 0; it < kV_0.size(); ++it)
    {
        if (std::abs(kV_0.at(it) - kV_1.at(it)) > 1e-3) return 0;
    }
    return 1;
}

TEST(TurboEncoderTests, encoding_test_0)
{
    std::vector<Bit_t> input{ 1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0 };
    std::vector<Bit_t> out_expected{ 1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,0,0,0,1,1 };
    std::vector<Bit_t> out_actual;

    TurboEncoder encoder;
    encoder.Encode(input, out_actual);
    ASSERT_TRUE(CompareVector(out_expected, out_actual));
}

TEST(TurboEncoderTests, encoding_test_1)
{
    std::vector<Bit_t> input{ 1,0,0,0,1,1,0,1,1,1,0,0,1,0,1,1 };
    std::vector<Bit_t> out_expected{ 1,1,1,0,1,1,0,1,1,0,0,1,1,0,1,1,1,0,0,0,0,1,1,0,1,0,1,1,1,0,0,0,1,0,0,1,1,1,0,0,1,0,1,0,1,1,0,0 };
    std::vector<Bit_t> out_actual;

    TurboEncoder encoder;
    encoder.Encode(input, out_actual);
    ASSERT_TRUE(CompareVector(out_expected, out_actual));
}

TEST(TurboEncoderTests, encoding_zeros_test)
{
    std::vector<Bit_t> input(16,0);
    std::vector<Bit_t> out_expected(48, 0);
    std::vector<Bit_t> out_actual;

    TurboEncoder encoder;
    encoder.Encode(input, out_actual);
    ASSERT_TRUE(CompareVector(out_expected, out_actual));
}

TEST(TurboEncoderTests, encoding_empty_vector)
{
    std::vector<Bit_t> input;
    std::vector<Bit_t> out_actual;

    TurboEncoder encoder;
    encoder.Encode(input, out_actual);
    ASSERT_TRUE(out_actual.size() == 0);
}

TEST(TurboEncoderTests, encoding_invalid_vector)
{
    std::vector<Bit_t> input{ 0,1,2,3,4,5 };
    std::vector<Bit_t> out_actual;
    TurboEncoder encoder;
    ASSERT_ANY_THROW(encoder.Encode(input, out_actual););
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

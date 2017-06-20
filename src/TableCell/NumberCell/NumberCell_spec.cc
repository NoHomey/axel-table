#include "NumberCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(NumberCell, getValueAsNumber) {
    IT("should return the Number with which it was created");
    EXPECT_EQ(NumberCell{{}}.getValueAsNumber().getInteger(), 0);
    EXPECT_EQ(NumberCell{(long long)9}.getValueAsNumber().getInteger(), 9);
    EXPECT_EQ(NumberCell{(long long)-54427}.getValueAsNumber().getInteger(), -54427);
    EXPECT_EQ(NumberCell{(long long)30}.getValueAsNumber().getInteger(), 30);
    EXPECT_EQ(NumberCell{(long long)-54}.getValueAsNumber().getInteger(), -54);
    EXPECT_DOUBLE_EQ(NumberCell{2.345}.getValueAsNumber().getReal(), 2.345);
    EXPECT_DOUBLE_EQ(NumberCell{-2.345}.getValueAsNumber().getReal(), -2.345);
    EXPECT_DOUBLE_EQ(NumberCell{0.5}.getValueAsNumber().getReal(), 0.5);
}

TEST(NumberCell, calculateLengthsWhenIntegerWithLessThan17Digits) {
    IT("should return the length of Number's value string representation");
    
    const long long values[] = {0, 1, 2, -1, -2, 10, 304, -443, 12434, -34344,
    304349, -19283848, 1202329, 83438414, 38438823, -349384381889, -2323434143413,
    393349294293294, -393349294293294, 123456789012345, -123456789012345,
    3933492942932941, -3933492942932942, 1234567890123453, -1223456789012345};

    const size_t expects[] = {1, 1, 1, 2, 2, 2, 3, 4, 5, 6, 6, 9, 7, 8, 8, 13,
    14, 15, 16, 15 , 16, 16, 17, 16, 17};

    for(int i = 0; i < 25; ++i) {
        NumberCell cell = {(const long long)values[i]};
        EXPECT_EQ(cell.calculateOutputLength(), expects[i]);
        EXPECT_EQ(cell.calculateSerializedLength(), expects[i]);
    }
}

TEST(NumberCell, calculateLengthsWhenIntegerWithMoreThan16Digits) {
    IT("should return the length of Number's value string representation limited to 16 digits");
    
    const long long values[] = {39334929429329410, -39334929402932942, 12345678901123453, -12223456789012345,
    922337203685477580, -9223372036854775807, 712327203685467384, -712327203685467384};

    const size_t expects[] = {16, 17, 16 , 17, 16, 17, 16, 17};

    for(int i = 0; i < 8; ++i) {
        NumberCell cell = {(const long long)values[i]};
        EXPECT_EQ(cell.calculateOutputLength(), expects[i]);
        EXPECT_EQ(cell.calculateSerializedLength(), expects[i]);
    }
}

TEST(NumberCell, calculateLengthsWhenRealWithLessThan17Digits) {
    IT("should return the length of Number's value string representation");
    
    const double values[] = {0.3, 1.12, 2.01, -1.343, -2.34, 10.4545,
    304.334, -443.34313, 12434.3244, -34344.32424,
    304349.3434, -19283848.23, 1202329.0, 834.8414, -3843.23, -349384381889.000, -2323434143413,
    -39.4929402932942, -39334.294224, 12345789.112345, -12345678.012345,
    3933492942.32941, -1111.0429123442, 123.567890123453, -122345678901.345};

    const size_t expects[] = {3, 4, 4, 6, 5, 7, 7, 10, 10, 12, 11, 12, 7, 8, 8, 13,
    14, 17, 13, 15 , 16, 16, 16, 16, 17};

    for(int i = 0; i < 25; ++i) {
        NumberCell cell = {values[i]};
        EXPECT_EQ(cell.calculateOutputLength(), expects[i]);
        EXPECT_EQ(cell.calculateSerializedLength(), expects[i]);
    }
}

TEST(NumberCell, calculateLengthsWhenRealWithMoreThan16Digits) {
    IT("should return the length of Number's value string representation limited to 16 digits");
    
    double values[] = {3933492429.9410121, -391.4929402932942, 1234567.01123453, -1223.456789012345,
    9223372.85477580, -922337.854775807, 71232720.5467384, -71232720368.67384};

    const size_t expects[] = {17, 18, 17 , 18, 17, 18, 17, 18};

    for(int i = 0; i < 8; ++i) {
        NumberCell cell = {values[i]};
        EXPECT_EQ(cell.calculateOutputLength(), expects[i]);
        EXPECT_EQ(cell.calculateSerializedLength(), expects[i]);
    }
}
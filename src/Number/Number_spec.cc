#include "Number.h"
#include "gtest/gtest.h"
#include "../It/It.h"
#include "NumberHelper.h"

TEST(Number, addition) {
    {
        Number a = static_cast<const long long>(9);
        Number b = static_cast<const long long>(1);
        Number c = a + b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 10);

        c += c;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 20);
    }
    
    {
        Number a = static_cast<const long long>(9);
        Number b = 1.33;
        Number c = a + b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 10.33);

        c += c;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 20.66);
    }

    {
        Number a = 9.2;
        Number b = static_cast<const long long>(2);
        Number c = a + b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 11.2);

        c += c;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 22.4);
    }

    {
        Number a = 7.4;
        Number b = 2.5;
        Number c = a + b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 9.9);

        c += c;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 19.8);
    }

    {
        Number a = static_cast<const long long>(99);
        Number b = static_cast<const long long>(111);
        Number c = a + b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 210);

        c += c;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 420);
    }
    
    {
        Number a = static_cast<const long long>(98);
        Number b = 1.33780;
        Number c = a + b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 99.33780);

        c += c;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 198.6756);
    }

    {
        Number a = 9.23;
        Number b = static_cast<const long long>(23);
        Number c = a + b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 32.23);

        c += c;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 64.46);
    }

    {
        Number a = 7.4244;
        Number b = 2.511986;
        Number c = a + b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 9.936386);

        c += c;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 19.872772);
    }
}


TEST(Number, substraction) {
    {
        Number a = static_cast<const long long>(9);
        Number b = static_cast<const long long>(1);
        Number c = a - b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 8);

        c -= b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 7);
    }
    
    {
        Number a = static_cast<const long long>(9);
        Number b = 1.33;
        Number c = a - b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 7.67);

        c -= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 6.34);
    }

    {
        Number a = 9.2;
        Number b = static_cast<const long long>(2);
        Number c = a - b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 7.2);

        c -= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 5.2);
    }

    {
        Number a = 7.4;
        Number b = 2.5;
        Number c = a - b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 4.9);

        c -= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 2.4);
    }

    {
        Number a = static_cast<const long long>(99);
        Number b = static_cast<const long long>(111);
        Number c = a - b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), -12);

        c -= b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), -123);
    }
    
    {
        Number a = static_cast<const long long>(98);
        Number b = 1.33780;
        Number c = a - b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 96.6622);

        c -= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 95.3244);
    }

    {
        Number a = 9.23;
        Number b = static_cast<const long long>(23);
        Number c = a - b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), -13.77);

        c -= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), -36.77);
    }

    {
        Number a = 7.4244;
        Number b = 2.511986;
        Number c = a - b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 4.912414);

        c -= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 2.400428);
    }
}

TEST(Number, multiplication) {
    {
        Number a = static_cast<const long long>(9);
        Number b = static_cast<const long long>(1);
        Number c = a * b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 9);

        c *= c;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 81);
    }
    
    {
        Number a = static_cast<const long long>(9);
        Number b = 1.33;
        Number c = a * b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 11.97);

        c *= c;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 143.2809);
    }

    {
        Number a = 9.2;
        Number b = static_cast<const long long>(2);
        Number c = a * b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 18.4);

        c *= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 36.8);
    }

    {
        Number a = 7.4;
        Number b = 2.5;
        Number c = a * b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 18.5);

        c *= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 46.25);
    }

    {
        Number a = static_cast<const long long>(99);
        Number b = static_cast<const long long>(111);
        Number c = a * b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 10989);

        c *= a;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 1087911);
    }
    
    {
        Number a = static_cast<const long long>(98);
        Number b = 1.33780;
        Number c = a * b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 131.1044);

        c *= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 175.39146632);
    }

    {
        Number a = 9.23;
        Number b = static_cast<const long long>(23);
        Number c = a * b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 212.29);

        c *= c;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 45067.0441);
    }

    {
        Number a = 7.4244;
        Number b = 2.51000;
        Number c = a * b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 18.635244);

        c *= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 46.77446244);
    }
}
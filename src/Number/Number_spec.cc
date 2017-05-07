#include "Number.h"
#include "gtest/gtest.h"
#include "../It/It.h"
#include "NumberHelper.h"

TEST(Number, opposite) {
    IT("returns the addition invers of a number");

    const long long ints[] = {1, -3, 5, -8, 9, 0, -23, 34, 456, -978, 1234, -8091, 18434, 34351, -343578};

    const double reals[] = {0.23, 0.1, 1.2, -3.4, -5.67, -98.01, 1243.3434, -53.5665, -834.003434, 0.76};

    for(int i = 0; i < 15; ++i) {
        EXPECT_EQ(NumberHelper{Number{ints[i]}}.getInteger(), ints[i]);
        EXPECT_EQ(NumberHelper{Number{-ints[i]}}.getInteger(), -ints[i]);
        EXPECT_EQ(NumberHelper{-Number{ints[i]}}.getInteger(), -ints[i]);
        EXPECT_EQ(NumberHelper{-Number{-ints[i]}}.getInteger(), ints[i]);
        EXPECT_EQ(NumberHelper{-(-Number{ints[i]})}.getInteger(), ints[i]);
        EXPECT_EQ(NumberHelper{-(-Number{-ints[i]})}.getInteger(), -ints[i]);
    }

    for(int i = 0; i < 10; ++i) {
        EXPECT_DOUBLE_EQ(NumberHelper{Number{reals[i]}}.getReal(), reals[i]);
        EXPECT_DOUBLE_EQ(NumberHelper{Number{-reals[i]}}.getReal(), -reals[i]);
        EXPECT_DOUBLE_EQ(NumberHelper{-Number{reals[i]}}.getReal(), -reals[i]);
        EXPECT_DOUBLE_EQ(NumberHelper{-Number{-reals[i]}}.getReal(), reals[i]);
        EXPECT_DOUBLE_EQ(NumberHelper{-(-Number{reals[i]})}.getReal(), reals[i]);
        EXPECT_DOUBLE_EQ(NumberHelper{-(-Number{-reals[i]})}.getReal(), -reals[i]);
    }
}

TEST(Number, addition) {
    IT("adds two numbers");

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
    IT("substracts two numbers");

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
    IT("multiplies two numbers");
    
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


TEST(Number, division) {
    IT("divides two numbers and sets the result to be real number");

    {
        Number a = static_cast<const long long>(1);
        Number b = static_cast<const long long>(9);
        Number c = a / b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 0.1111111111111111);

        c /= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 0.012345679012345678);
    }
    
    {
        Number a = static_cast<const long long>(9);
        Number b = 1.33;
        Number c = a / b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 6.7669172932330826);

        c /= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 5.0879077392729943);
    }

    {
        Number a = 9.2;
        Number b = static_cast<const long long>(2);
        Number c = a / b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 4.6);

        c /= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 2.3);
    }

    {
        Number a = 7.4;
        Number b = 2.5;
        Number c = a / b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 2.96);

        c /= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 1.184);
    }

    {
        Number a = static_cast<const long long>(99);
        Number b = static_cast<const long long>(111);
        Number c = a / b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 0.89189189189189189);

        c /= a;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 0.0090090090090090089);
    }
    
    {
        Number a = static_cast<const long long>(98);
        Number b = 1.33780;
        Number c = a / b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 73.254597099715951);

        c /= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 54.757510165731759);
    }

    {
        Number a = 9.23;
        Number b = static_cast<const long long>(23);
        Number c = a / b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 0.40130434782608698);

        c /= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 0.017448015122873348);
    }

    {
        Number a = 7.4244;
        Number b = 2.51000;
        Number c = a / b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 2.95792828685259);

        c /= c;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 1);
    }
}

TEST(Number, divisionByZero) {
    IT("throws DivisionByZero");

    const Number intZero = static_cast<const long long>(0);
    const Number zero = 0.0;

    for(long long n = 0; n < 13; ++n) {
        EXPECT_THROW(Number{n} / intZero, Number::DivisionByZero);
        EXPECT_THROW(Number{-n} / intZero, Number::DivisionByZero);
        EXPECT_THROW(Number{n} / zero, Number::DivisionByZero);
        EXPECT_THROW(Number{-n} / zero, Number::DivisionByZero);
    }
}

TEST(Number, raisingZeroOnNegativePower) {
    IT("throws DivisionByZero");

    const Number intZero = static_cast<const long long>(0);
    const Number zero = 0.0;

    for(long long n = -1; n > -13; --n) {
        EXPECT_THROW(intZero ^ n, Number::DivisionByZero);
        EXPECT_THROW(zero ^ n, Number::DivisionByZero);
    }
}

TEST(Number, raisingZeroOnZeroPower) {
    IT("throws ZeroRaisedOnZero");

    const Number intZero = static_cast<const long long>(0);
    const Number zero = 0.0;

    EXPECT_THROW(intZero ^ intZero, Number::ZeroRaisedOnZero);
    EXPECT_THROW(intZero ^ zero, Number::ZeroRaisedOnZero);
    EXPECT_THROW(zero ^ intZero, Number::ZeroRaisedOnZero);
    EXPECT_THROW(zero ^ zero, Number::ZeroRaisedOnZero);
}

TEST(Number, raisingZeroOnPositivePower) {
    IT("evaluates to zero");

    const Number intZero = static_cast<const long long>(0);
    const Number zero = 0.0;

    for(long long n = 1; n > 13; ++n) {
        EXPECT_EQ(NumberHelper{intZero ^ n}.getInteger(), 0);
        EXPECT_EQ(NumberHelper{zero ^ n}.getInteger(), 0);
    }
}

TEST(Number, raisingOnPowerWhenExponentIsZero) {
    IT("should always evaluate to integer 1");

    const long long intBases[] = {9999, -33434, -34343, 232, -10, 1, 9, 2323, -1, 4, 999999, -12345};

    const double realBases[] = {1.3343, -343.3434, 0.0001, -0.0009, 23.3, -16.4, -17.3215,
                42.420240, 9999.9999, 12343.4534535, -453934.324928};

    const Number zero = static_cast<const long long>(0);

    for(size_t i = 0; i < 11; ++i) {
        EXPECT_EQ((NumberHelper{Number{intBases[i]} ^ zero}).getInteger(), 1);
        EXPECT_EQ((NumberHelper{Number{realBases[i]} ^ zero}).getInteger(), 1);
    }
}

TEST(Number, raisingOnIntegerPower) {
    IT("raises one number on power of another number");

    {   Number a = static_cast<const long long>(1);
        Number b = static_cast<const long long>(-1);
        Number c = a ^ b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 1);

        c = b ^ a;
        EXPECT_EQ(NumberHelper{c}.getInteger(), -1);
    }

    {   Number a = static_cast<const long long>(-1);
        Number b = static_cast<const long long>(9);
        Number c = static_cast<const long long>(8);
        EXPECT_EQ(NumberHelper{a ^ b}.getInteger(), -1);
        EXPECT_EQ(NumberHelper{a ^ c}.getInteger(), 1);
    }

    {   Number a = static_cast<const long long>(-10);
        Number b = static_cast<const long long>(2);
        Number c = a ^ b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 100);

        c ^= b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), 10000);
    }

    {   Number a = -3.5;
        Number b = static_cast<const long long>(2);
        Number c = a ^ b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 12.25);

        c ^= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 150.0625);
    }

    {   Number a = static_cast<const long long>(-2);
        Number b = static_cast<const long long>(5);
        Number c = a ^ b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), -32);

        c ^= b;
        EXPECT_EQ(NumberHelper{c}.getInteger(), -33554432);
    }

    {   Number a = 1.23;
        Number b = static_cast<const long long>(7);
        Number c = a ^ b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 4.2592759697774696);

        c ^= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 25430.240096337577);
    }

    {   Number a = static_cast<const long long>(3);
        Number b = static_cast<const long long>(-3);
        Number d = static_cast<const long long>(-4);
        Number c = a ^ b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 0.037037037037037035);

        c ^= d;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 531441);
    }

    {   Number a = -1.23;
        Number b = static_cast<const long long>(-7);
        Number c = a ^ b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), -0.23478168756748721);

        c ^= b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), -25430.240096337577);
    }

    {   Number a = static_cast<const long long>(-3);
        Number b = static_cast<const long long>(-1);
        Number d = static_cast<const long long>(-4);
        Number c = a ^ b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), -0.3333333333333333);

        c ^= d;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), 81);
    }

    {   Number a = -6.300;
        Number b = static_cast<const long long>(-5);
        Number d = static_cast<const long long>(-3);
        Number c = a ^ b;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), -0.00010076210988534711);

        c ^= d;
        EXPECT_DOUBLE_EQ(NumberHelper{c}.getReal(), -977480813971.14502);
    }
}

TEST(Number, raisingOnIntegerPowerWhenBaseIsPowerOfTwo) {
    IT("should properly raise integer which is powerOfTwo");

    struct RaisingExpect {
        const long long raisingPositveOnPositive;
        const long long raisingNegativeOnPositive;
        const double raisingPositveOnNegative;
        const double raisingNegativeOnNegative;
    };

    RaisingExpect expects[] = {
        {16, -32, 0.0625, -0.03125},
        {256, -1024, 0.00390625, -0.0009765625},
        {4096, -32768, 0.000244140625, -0.000030517578125}
    };

    const Number four = static_cast<const long long>(4);
    const Number five = static_cast<const long long>(5);
    const Number negativeFour = static_cast<const long long>(-4);
    const Number negativeFive = static_cast<const long long>(-5);

    long long base = 2;

    for(size_t i = 0; i < 3; ++i) {
        Number positive = base;
        Number negative = -base;
        EXPECT_EQ((NumberHelper{positive ^ four}).getInteger(), expects[i].raisingPositveOnPositive);
        EXPECT_EQ((NumberHelper{negative ^ five}).getInteger(), expects[i].raisingNegativeOnPositive);
        EXPECT_EQ((NumberHelper{positive ^ negativeFour}).getReal(), expects[i].raisingPositveOnNegative);
        EXPECT_EQ((NumberHelper{negative ^ negativeFive}).getReal(), expects[i].raisingNegativeOnNegative);
        base <<= 1;
    }
}

template<typename Type>
struct TestRaisingOnRealPower {
    const Type base;
    const double exponent;
    const double expect;
};

TEST(Number, raisingPositiveNumberOnPositiveeRealPower) {
    IT("raises one number on power of another number");

    TestRaisingOnRealPower<long long> intTest[] = {
        {1, 0.1, 1},
        {3, 0.3, 1.3903891703159093},
        {5, 1.2, 6.8986483073060736},
        {91, 3.3, 2916329.5248532863}
    };

    for(size_t i = 0; i < 4; ++i) {
        EXPECT_DOUBLE_EQ(NumberHelper{Number{intTest[i].base} ^ intTest[i].exponent}.getReal(), intTest[i].expect);
    }

    TestRaisingOnRealPower<double> realTest[] = {
        {1.3, 0.1, 1.026583631304232},
        {3.2, 0.3, 1.4175715661678827},
        {5.6, 1.2, 7.9036123723983769},
        {9119.8876, 1.12, 27238.815880581664}
    };

    for(size_t i = 0; i < 4; ++i) {
        EXPECT_DOUBLE_EQ(NumberHelper{Number{realTest[i].base} ^ realTest[i].exponent}.getReal(), realTest[i].expect);
    }
}

TEST(Number, raisingPositiveNumberOnNegativeRealPower) {
    IT("raises one number on power of another number");

    TestRaisingOnRealPower<long long> intTest[] = {
        {1, -0.1, 1},
        {3, -0.3, 0.71922309332486434},
        {5, -1.2, 0.14495593273553911}
    };

    for(size_t i = 0; i < 3; ++i) {
        EXPECT_DOUBLE_EQ(NumberHelper{Number{intTest[i].base} ^ intTest[i].exponent}.getReal(), intTest[i].expect);
    }

    TestRaisingOnRealPower<double> realTest[] = {
        {1.3, -0.1, 0.97410475825485487},
        {3.2, -0.3, 0.70543175658023194},
        {5.6, -1.2, 0.12652442362840052}
    };

    for(size_t i = 0; i < 3; ++i) {
        EXPECT_DOUBLE_EQ(NumberHelper{Number{realTest[i].base} ^ realTest[i].exponent}.getReal(), realTest[i].expect);
    }
}

TEST(Number, raisingNegativeNumberOnRealPower) {
    IT("throws NegativeNumberRaisedOnNoneIntegerPower");

    const double power[] = {1.3, 1.2, 1.98, 2.34, 21.7, 13.76, 15.89, 982.23, 1243.34394, 0.124, 0.237};

    for(long long n = 1; n < 12; ++n) {
        Number a = -n;
        Number b = -power[n - 1];
        Number c = power[n - 1];
        EXPECT_THROW(a ^ c, Number::NegativeNumberRaisedOnNoneIntegerPower);
        EXPECT_THROW(a ^ b, Number::NegativeNumberRaisedOnNoneIntegerPower);
        EXPECT_THROW(b ^ c, Number::NegativeNumberRaisedOnNoneIntegerPower);
        EXPECT_THROW(b ^ b, Number::NegativeNumberRaisedOnNoneIntegerPower);
    }
}

TEST(Number, raisingZeroOnNegativeRealPower) {
    IT("throws DivisionByZero");

    const double power[] = {-1.3, -1.2, -1.98, -2.34, -21.7, -13.76, -15.89, -982.23, -1243.34394, -0.124, -0.237};

    const Number intZero = static_cast<const long long>(0);

    const Number zero = 0.0;

    for(long long i = 0; i < 11; ++i) {
        Number r = power[i];
        EXPECT_THROW(intZero ^ r, Number::DivisionByZero);
        EXPECT_THROW(zero ^ r, Number::DivisionByZero);
    }
}

TEST(Number, raisingZeroOnRealZeroPower) {
    IT("throws ZeroRaisedOnZero");
    const Number intZero = static_cast<const long long>(0);
    const Number zero = 0.0;
    EXPECT_THROW(intZero ^ zero, Number::ZeroRaisedOnZero);
    EXPECT_THROW(zero ^ zero, Number::ZeroRaisedOnZero);
}
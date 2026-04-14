/**
 * File: GMath.cpp
 * Purpose: To consolidate all concepts till day-6 into GMath library
 * Author: Varad Lanke
 * Date: April 15, 2026
 * Compilation: g++ GMath.cpp -o app
 * Execution: ./app
 */

#include <iostream>
#include <cmath>
#include <limits>
#include <cassert>
#include <exception>

/** Namespace that includes all mathematical functions related to mathematics*/
namespace gm
{
    /**
     * Function to get square of a number
     */
    template<typename T>
    constexpr T square(const T& number) { return number * number; }

    /**
     * Function to get cube of a number
     */
    template<typename T>
    constexpr T cube(const T& number) { return number * number * number; }

    /**
     * Function to check the Divisor is Zero or not
     */
    template<typename T>
    constexpr bool isDivisorZero(const T& number)
    {
        const T epsilon = (T)(1e-10);
        if(std::abs(number) < epsilon) return true;
        return false;
    }

    /**
     * Specialized Template Function to check the Divisor is Zero or not
     */
    template<>
    constexpr bool isDivisorZero<int>(const int& number)
    {
        return number == 0;
    }

    /**
     * Description: Function takes coefficients a, b, and c and return the roots. 
     *              Discriminant (D=b^2−4ac):
     *                  - D>0: Two real roots (the ray enters and exits the sphere).
     *                  - D=0: One real root (the ray is tangent to the sphere).
     *                  - D<0: No real roots (the ray misses the sphere).
     * 
     *              Example: 2x^2 − 4x − 6 = 0
     *                      a = 2, b = -4, c = -6
     *                      D = (−4)^2 − 4*(2)*(−6) = 16 + 48 = 64
     *                      Roots : x = 3 and x = -1
     */
    template <typename T = double>
    auto solveQuadraticEquation = [](const T& a, const T& b, const T& c) -> std::pair<double, double> {
        std::string res = "";

        T D = (b * b) - (4 * a * c);

        // validate 'a'
        if(gm::isDivisorZero(a))
        {
            throw std::invalid_argument("Invalid parameter 'a'! It must be Non-Zero");
        }

        // determine the root behaviour
        if(D > 0) res = "Two Real Roots";
        else if (D == 0) res = "One Real Root";
        else 
        {
            res = "No Real Roots";
            std::cout << "[INFO] The Quadratic equation has " << res << std::endl;
            return { std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN() };
        }

        std::cout << "[INFO] The Quadratic equation has " << res << std::endl;

        return { (-b + std::sqrt(D)) / (2 * a), (-b - std::sqrt(D)) / (2 * a) };
    };

};

/** -------- Namespace that includes all test cases for functions in gm namespace --------*/
namespace test
{

    void test_square()
    {
        int iNum = 2;
        long lNum = 3l;
        float fNum = 4.1f;
        double dNum = 5.2321;

        std::cout << "[INFO] Square of integer " << iNum << " = " << gm::square(iNum) << std::endl;
        std::cout << "[INFO] Square of long " << lNum << " = " << gm::square(lNum) << std::endl;
        std::cout << "[INFO] Square of float " << fNum << " = " << gm::square(fNum) << std::endl;
        std::cout << "[INFO] Square of double " << dNum << " = " << gm::square(dNum) << std::endl;
    }

    void test_cube()
    {
        int iNum = 2;
        long lNum = 3l;
        float fNum = 4.1f;
        double dNum = 5.2321;

        std::cout << "[INFO] Cube of integer " << iNum << " = " << gm::cube(iNum) << std::endl;
        std::cout << "[INFO] Cube of long " << lNum << " = " << gm::cube(lNum) << std::endl;
        std::cout << "[INFO] Cube of float " << fNum << " = " << gm::cube(fNum) << std::endl;
        std::cout << "[INFO] Cube of double " << dNum << " = " << gm::cube(dNum) << std::endl;
    }

    void test_isDivisorZero()
    {
        int iNum = 0;
        float fNum1 = 0.001;
        double dNum2 = 1.0000001;
        double dNum3 = 0.000000000001; // expected to be Zero as it is '1e-12'

        std::cout << "[INFO] isDivisorZero(" << iNum << ") = " << ( (gm::isDivisorZero(iNum)? "YES" : "NO") ) << std::endl;
        std::cout << "[INFO] isDivisorZero(" << fNum1 << ") = " << ( (gm::isDivisorZero(fNum1)? "YES" : "NO") ) << std::endl;
        std::cout << "[INFO] isDivisorZero(" << dNum2 << ") = " << ( (gm::isDivisorZero(dNum2)? "YES" : "NO") ) << std::endl;
        std::cout << "[INFO] isDivisorZero(" << dNum3 << ") = " << ( (gm::isDivisorZero(dNum3)? "YES" : "NO") ) << std::endl;

    }

    /** Test case: To test the real roots of the quadratic equation
     *  Example: 2x² − 4x − 6 = 0
     *          a = 2, b = -4, c = -6
     *          D = (−4)² − 4*(2)*(−6) = 16 + 48 = 64
     *          Roots : x = 3 and x = -1
     */
    void test_solveQuadraticEquation_TwoRealRoots()
    {
        int a = 2;
        int b = -4;
        int c = -6;

        auto res = gm::solveQuadraticEquation<int>(a, b, c);
        std::cout << "[INFO] Roots of " << a << "x²" << ((b<0)? "":"+") << b << "x"
                    << ((c<0)?"":"+") << c << " are : "
                    << res.first << " and " << res.second << std::endl;
    }

    /** Test case: To test the only one real root of the quadratic equation
     *  Example: x² − 4x + 4 = 0
     *          a = 1, b = -4, c = 4
     *          D = (-4)² − 4*(1)*(4) = 16 - 16 = 0
     *          Roots : x = 2 and x = 2
     */
    void test_solveQuadraticEquation_OneRealRoot()
    {
        int a = 1;
        int b = -4;
        int c = 4;

        auto res = gm::solveQuadraticEquation<int>(a, b, c);
        std::cout << "[INFO] Roots of " << a << "x²" << ((b<0)? "":"+") << b << "x"
                    << ((c<0)?"":"+") << c << " are : "
                    << res.first << " and " << res.second << std::endl;
    }

    /** Test case: To test the real roots of the quadratic equation
     *  Example: x² + 2x + 5 = 0
     *          a = 1, b = 2, c = 5
     *          D = (2)² − 4*(1)*(5) = 4 - 20 = -16
     *          Roots : x = NaN and x = NaN
     */
    void test_solveQuadraticEquation_NoRealRoots()
    {
        int a = 1;
        int b = 2;
        int c = 5;

        auto res = gm::solveQuadraticEquation<int>(a, b, c);
        assert(std::isnan(res.first) && std::isnan(res.second));

        std::cout << "[INFO] Roots of " << a << "x²" << ((b<0)? "":"+") << b << "x"
                    << ((c<0)?"":"+") << c << " are : "
                    << res.first << " and " << res.second << std::endl;
    }

    /** Test case: To test the Quadratic equation solver function with a as 0;
     */
    void test_solveQuadraticEquation_Invalid()
    {
        int a = 0;
        int b = 2;
        int c = 5;

        try
        {
            gm::solveQuadraticEquation<int>(a, b, c);
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "[INFO] 'a' is Zero | Test Passed" << std::endl;
        }
    }
}

int main()
{
    try
    {
        std::cout << "[INFO] GMath.cpp" << std::endl;

        std::cout << "\n[INFO] -------- Testing Square Function --------" << std::endl;
        test::test_square();

        std::cout << "\n[INFO] -------- Testing Cube Function --------" << std::endl;
        test::test_cube();

        std::cout << "\n[INFO] -------- Testing is Divisor zero or not Function --------" << std::endl;
        test::test_isDivisorZero();

        std::cout << "\n[INFO] -------- Testing Quadratic Solver Function --------" << std::endl;
        test::test_solveQuadraticEquation_TwoRealRoots(); // D > 0
        test::test_solveQuadraticEquation_OneRealRoot(); // D == 0
        test::test_solveQuadraticEquation_NoRealRoots(); // D < 0
        test::test_solveQuadraticEquation_Invalid(); // D < 0
    }
    catch (const std::exception& e)
    {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }

    return 0;
}

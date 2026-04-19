#ifndef TEST_HPP
#define TEST_HPP

/**
 * File: test.hpp
 * Purpose: To test the GMath functionality (unit tests)
 * Author: Varad Lanke
 * Date: April 20, 2026
 */

#include "GMath.hpp"

/** -------- Namespace that includes all test cases for functions in gm namespace --------*/
namespace test
{
    void test_square()
    {
        constexpr int iNum = 2;
        constexpr long lNum = 3l;
        constexpr float fNum = 4.1f;
        constexpr double dNum = 5.2321;

        std::cout << "[INFO] Square of integer " << iNum << " = " << gm::square(iNum) << std::endl;
        std::cout << "[INFO] Square of long " << lNum << " = " << gm::square(lNum) << std::endl;
        std::cout << "[INFO] Square of float " << fNum << " = " << gm::square(fNum) << std::endl;
        std::cout << "[INFO] Square of double " << dNum << " = " << gm::square(dNum) << std::endl;
    }

    void test_cube()
    {
        constexpr int iNum = 2;
        constexpr long lNum = 3l;
        constexpr float fNum = 4.1f;
        constexpr double dNum = 5.2321;

        std::cout << "[INFO] Cube of integer " << iNum << " = " << gm::cube(iNum) << std::endl;
        std::cout << "[INFO] Cube of long " << lNum << " = " << gm::cube(lNum) << std::endl;
        std::cout << "[INFO] Cube of float " << fNum << " = " << gm::cube(fNum) << std::endl;
        std::cout << "[INFO] Cube of double " << dNum << " = " << gm::cube(dNum) << std::endl;
    }

    void test_isZero()
    {
        constexpr int iNum = 0;
        constexpr float fNum1 = 0.001;
        constexpr double dNum2 = 1.0000001;
        constexpr double dNum3 = 0.000000000001; // expected to be Zero as it is '1e-12'

        std::cout << "[INFO] isZero(" << iNum << ") = " << ( (gm::isZero(iNum)? "YES" : "NO") ) << std::endl;
        std::cout << "[INFO] isZero(" << fNum1 << ") = " << ( (gm::isZero(fNum1)? "YES" : "NO") ) << std::endl;
        std::cout << "[INFO] isZero(" << dNum2 << ") = " << ( (gm::isZero(dNum2)? "YES" : "NO") ) << std::endl;
        std::cout << "[INFO] isZero(" << dNum3 << ") = " << ( (gm::isZero(dNum3)? "YES" : "NO") ) << std::endl;

    }

    /** Test case: To test the real roots of the quadratic equation
     *  Example: 2x² − 4x − 6 = 0
     *          a = 2, b = -4, c = -6
     *          D = (−4)² − 4*(2)*(−6) = 16 + 48 = 64
     *          Roots : x = 3 and x = -1
     */
    void test_solveQuadraticEquation_TwoRealRoots()
    {
        constexpr int a = 2;
        constexpr int b = -4;
        constexpr int c = -6;

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
        constexpr int a = 1;
        constexpr int b = -4;
        constexpr int c = 4;

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
        constexpr int a = 1;
        constexpr int b = 2;
        constexpr int c = 5;

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
        constexpr int a = 0;
        constexpr int b = 2;
        constexpr int c = 5;

        try
        {
            gm::solveQuadraticEquation<int>(a, b, c);
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << "[INFO] 'a' is Zero | Test Passed" << std::endl;
        }
    }

    /**
     * Complex number tests
     */
    void test_complex_operations()
    {
        std::cout << std::fixed << std::setprecision(2);

        // double test
        const gm::Complex<double> c1(1.0, 2.0);
        const gm::Complex<double> c2(2.0, 4.0);
        std::cout << "[INFO] c1+c2 = " << c1 << "+" << c2 << " = " << c1 + c2 << std::endl;
        std::cout << "[INFO] c1-c2 = " << c1 << "-" << c2 << " = " << c1 - c2 << std::endl;
        std::cout << "[INFO] c1*c2 = " << c1 << "*" << c2 << " = " << c1 * c2 << std::endl;

        // integer test
        const gm::Complex<int> c3(11, 22);
        const gm::Complex<int> c4(33, 55);
        std::cout << "[INFO] c3+c4 = " << c3 << "+" << c4 << " = " << c3 + c4 << std::endl;
        std::cout << "[INFO] c3*c4 = " << c3 << "*" << c4 << " = " << c3 * c4 << std::endl;

        // equal test
        const gm::Complex<double> c7(2.0, 4.0);
        if(c2 == c7)
            std::cout << "[INFO] c2: " << c2 << " == c7: " << c7 << std::endl;

        // zero divide test
        try
        {
            const gm::Complex<double> c5(0.0, 0.0);
            const gm::Complex<double> c6(0.0, 0.0);
            std::cout << "[INFO] c5/c6 = " << c5 << "/" << c6 << " = " << c5 / c6 << std::endl;
        }
        catch (const std::exception& ex)
        {
            std::cout << std::endl << "[INFO] Test Passed : " << ex.what() << std::endl;
        }

        return;
    }

    /**
     * Test Trigonometric Functions
     * 
     */
    void test_trigonometric_functions()
    {
        constexpr double angleInDegrees = 30.0;
        constexpr double angleInRadians = gm::PI<double>;
        constexpr gm::Point<double> pt{2.0, 4.0, 0.0};

        std::cout << "[INFO] getRadians("<< angleInDegrees << ") = " << gm::getRadians(angleInDegrees) << std::endl;
        std::cout << "[INFO] gm::getDegrees("<< angleInRadians <<") = " << gm::getDegrees(angleInRadians) << std::endl;

        std::cout << "[INFO] rotateAntiClockwise(" << pt << "," << angleInRadians << ") = " << gm::rotateAC(pt, angleInRadians) << std::endl;

        return;
    }

    /**
     * Test Distance formula
     */
    void test_distanceFourmula()
    {
        // valid test
        gm::Point<double> p1{2.0, 5.0, 3.0};
        gm::Point<double> p2{3.2, 7.1, 6.8};
        auto res = gm::dist(p1, p2);

        std::cout << "[INFO]: Distance : d(P2"<< p2 << ",P1" << p1 << ") = " << res << std::endl;

        // -ve test
        p1 = {2.0, 5.0, 3.0};
        p2 = {-3.2, -7.1, -6.8};
        res = gm::dist(p1, p2);
        std::cout << "[INFO]: Distance : d(P2"<< p2 << ",P1" << p1 << ") = " << res << std::endl;

        // self test
        p1 = {2.0, 5.0, 3.0};
        p2 = {2.0, 5.0, 3.0};
        res = gm::dist(p1, p2);
        std::cout << "[INFO]: Distance : d(P2"<< p2 << ",P1" << p1 << ") = " << res << std::endl;

        return;
    }
}
#endif

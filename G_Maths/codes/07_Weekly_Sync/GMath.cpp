/**
 * File: GMath.cpp
 * Purpose: To consolidate all concepts till day-6 into GMath library
 * Author: Varad Lanke
 * Date: April 15, 2026
 * Compilation: g++ GMath.cpp -o app
 * Execution: ./app
 */

#include <iostream>
#include <iomanip>
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
    constexpr bool isZero(const T& number)
    {
        const T epsilon = (T)(1e-10);
        if(std::abs(number) < epsilon) return true;
        return false;
    }

    /**
     * Specialized Template Function to check the Divisor is Zero or not
     */
    template<>
    constexpr bool isZero<int>(const int& number)
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
        if(gm::isZero(a))
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

    /**
     * Class Name: Complex
     * Description: To perform operations related to complex numbers
     * Exmaple: (2-3i)
     */
    template <typename T = double>
    class Complex
    {
        private:
            T real;
            T img;

        public:
            Complex(T _real = (T)0, T _img = (T)0) : real(_real), img(_img) {}

            Complex<T> conjugate() const { return Complex<T>(real, -img); }

            T modulus() const { return std::sqrt(real*real + img*img); }

            Complex<T> operator+(const Complex<T>& other) const { return Complex<T>(real + other.real, img + other.img); }

            Complex<T> operator-(const Complex<T>& other) const { return Complex<T>(real - other.real, img - other.img); }

            /**
             * Function: Operator overload for multiplication operation of 2 Complex numbers
             * Multiplication Exmaple
             * n1 = a+bi
             * n2 = c+di
             * n1 x n2 = (a+bi) x (c+di)
             *         = a(c+di) + bi(c+di)
             *         = ac + adi + bci - bd
             * n1 x n2 = (ac-bd) + (ad+bc)i
             * 
             */
            Complex<T> operator*(const Complex<T>& other) const
            {
                /*T a = real;
                T b = img;
                T c = other.real;
                T d = other.img;
                return Complex((a*c - b*d), (a*d + b*c));*/

                return Complex(
                    (real * other.real - img * other.img),
                    (real * other.img + img * other.real)
                );
            }

            /**
             *  Function: Division of 2 complex numbers
             *  n1/n2 = (a+bi) / (c+di)
             *        = ((a+bi) * (c-di)) / ((c+di) * (c-di))
             *        = ((a+bi) * conjugate(n2)) / (c²-d²)
             *        = ((a+bi) * conjugate(n2)) / modulus²(n2)
             *        = (a'/ modulus²(n2)) + (b'i / modulus²(n2))
             */
            Complex<T> operator/(const Complex<T>& other) const 
            {
                // check divisor is zero or not
                auto numerator = (*this) * other.conjugate();
                T denom = other.modulus() * other.modulus();
                if(!isZero(denom))
                    return Complex((numerator.real / denom), (numerator.img / denom));
                else
                    throw std::runtime_error("Divide by Zero!!!");
            }

            constexpr bool operator==(const Complex& other) const
            {
                return (real == other.real && img == other.img);
            }

            friend std::ostream& operator<<(std::ostream& out, const Complex& other)
            {
                out << "(" << other.real << ((other.img < 0) ? "" : "+") << other.img << "i)";
                return out;
            }
    };


    /**
     * Trigonometric Functions
     */
    template <typename T = double>
    struct Point
    { 
        T x, y, z; 

        friend std::ostream& operator<<(std::ostream& out, const Point<T>& opt)
        {
            out << "(" << opt.x << "," << opt.y << "," << opt.z << ")";
            return out;
        }
    };

    template<typename T = double>
    constexpr T PI = (T)3.14159265358979323846;

    template<typename T = double>
    constexpr inline T getRadians(T angleInDegree) { return (angleInDegree*PI<T> / 180.0); }

    template<typename T = double>
    constexpr inline T getDegrees(T angleInRadian) { return (angleInRadian * 180.0 / PI<T>); }

    /**
     * Function : rotate point Anti Clockwise
     * Description: 
     * p1(x, y) and angle A
     * x' = x CosA - y SinA
     * y' = xSinA + yCosA
     * z' = 1
     */
    template<typename T>
    Point<T> rotateAC(const Point<T>& pt, T angle)
    {
        return { 
            (T)(((pt.x * std::cos(angle)) - (pt.y * std::sin(angle))),
            (T)((pt.x * std::sin(angle)) + (pt.y * std::cos(angle)))),
            (T)1.0 
        };
    }

    /**
     * Function : Distance between two points
     * Description: Apply Distance foumula
     *              dist(a, b) = sqrt((x2 - x1)² + (y2 - y1)²) + (z2 - z1)²;
     */
    template<typename T>
    T dist(const Point<T>& p1, const Point<T>& p2)
    {
        return std::sqrt(
            (p2.x - p1.x)*(p2.x - p1.x) +
            (p2.y - p1.y)*(p2.y - p1.y) +
            (p2.z - p1.z) * (p2.z - p1.z)
        );
    }

};

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
        test::test_isZero();

        std::cout << "\n[INFO] -------- Testing Quadratic Solver Function --------" << std::endl;
        test::test_solveQuadraticEquation_TwoRealRoots(); // D > 0
        test::test_solveQuadraticEquation_OneRealRoot(); // D == 0
        test::test_solveQuadraticEquation_NoRealRoots(); // D < 0
        test::test_solveQuadraticEquation_Invalid(); // a == 0

        std::cout << "\n[INFO] -------- Testing Complex Operatrion Function --------" << std::endl;
        test::test_complex_operations();

        std::cout << "\n[INFO] -------- Testing Trigonomtric Functions --------" << std::endl;
        test::test_trigonometric_functions();

        std::cout << "\n[INFO] -------- Testing Distance Formula Function --------" << std::endl;
        test::test_distanceFourmula();
    }
    catch (const std::exception& e)
    {
        std::cerr << std::endl << "[ERROR] " << e.what() << std::endl;
    }

    return 0;
}

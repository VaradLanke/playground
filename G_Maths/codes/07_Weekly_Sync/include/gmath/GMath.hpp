#ifndef GMATH_HPP
#define GMATH_HPP

/**
 * File: GMath.hpp
 * Purpose: To consolidate all concepts till day-6 into GMath library
 * Author: Varad Lanke
 * Date: April 20, 2026
 * Compilation: g++ -std=c++17 -I./include/gmath/ -I./tests/ src/main.cpp -o build/app
 * Execution: ./build/app
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
            (T)((pt.x * std::cos(angle)) - (pt.y * std::sin(angle))),
            (T)((pt.x * std::sin(angle)) + (pt.y * std::cos(angle))),
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

}
#endif

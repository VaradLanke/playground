/**
 * File: D3_E1_Exercise.cpp
 * Purpose: Simple Complex number class with arithmetic operations
 *          with conjugate and modulus support
 * Author: Varad Lanke
 * Date: March 31, 2026
 * Compilation: g++ D3_E1_Exercise.cpp -o app
 * Execution: ./app
 */

#include <iostream>
#include <cmath>

template<typename T>
class Complex
{
    private:
        T real;
        T img;

        void setReal(T _real) { real = _real; }

        void setImg(T _img) { img = _img; }

    public:
        Complex(T _real = 0 , T _img = 0): real(_real), img(_img) {}

        Complex operator+(const Complex& other)
        {
            return Complex((real + other.real), (img + other.img));
        }

        Complex operator-(const Complex& other)
        {
            return Complex((real - other.real),(img - other.img));
        }

        /**
         * For Understanding following is multiplication
         * (a + bi) x (c + di) =
         *  = a(c+di) + bi (c+di)
         *  = ac + adi + bci - bd
         *  = (ac - bd) + (ad + bc)i
        */
        Complex operator*(const Complex& other) const
        {
            T a = real, b = img;
            T c = other.real, d = other.img;
            return Complex(((a*c) - (b*d)), ((a*d) + (b*c)));
        }

        /**
         * (a + bi) / (c + di) = 
         *  = ((a + bi) * conjugate of divisor) / square of modulus of divisor
         *  = (a' / square of modulus of divisor) + (b'i / square of modulus of divisor)
         * Note: you can see the division formula in this file 'Complex_numbers_Division.jpeg'
         *  */        
        Complex operator/(const Complex& other) const
        {
            Complex numerator = (*this) * other.conjugate();
            auto denominator = other.modulus() * other.modulus();
            float epsilon = 1e-10f;
            if(std::abs(denominator) < epsilon)
            {
                std::cerr << "[ERROR] Cannot divide by zero!" << std::endl;
                return Complex();
            }
            return Complex( (numerator.real / denominator), (numerator.img / denominator));
        }

        bool operator==(const Complex& other) const
        {
            bool b1 = false;
            bool b2 = false;

            /*if(std::abs(real) == std::abs(other.real))  b1 = true;
            if(std::abs(img) == std::abs(other.img))  b2 = true;*/

            if(real == other.real)  b1 = true;
            if(img == other.img)  b2 = true;

            return b1 && b2;
        }

        /** 
         * Complex Conjugate (z): This is found by negating the imaginary part: a+bi=a−bi
         * This is a crucial step for performing division and finding inverses
        */
        Complex conjugate() const { return Complex(real, -img); }

        /**
         * |a+bi| = square root of a^2 + b^2
         * This represents the magnitude or "length" of the complex number
         */
        T modulus() const { return std::sqrt(real*real + img*img); }

        friend std::ostream& operator<<(std::ostream& out, const Complex& other)
        {
            out << "(" << other.real << ((other.img > 0) ? "+" : "") << other.img << "i)";
            return out;
        }

        ~Complex() {}
};

int main()
{
    //code
    Complex<double> c1(2.1, 3.1);
    Complex<double> c2(4.1, 5.1);
    //Complex<double> c2(0.000,0.000);

    std::cout << c1 << " + " << c2  << " = " << c1+c2 << std::endl;
    std::cout << c1 << " - " << c2  << " = " << c1-c2 << std::endl;
    std::cout << c1 << " x " << c2  << " = " << c1*c2 << std::endl;
    std::cout << c1 << " / " << c2  << " = " << c1/c2 << std::endl;
    std::cout << "Conjugate of " << c1 << " = " << c1.conjugate() << std::endl;
    std::cout << "Modulus of " << c1 << " = " << c1.modulus() << std::endl;

    if(c1 == c2)
        std::cout << c1 << " and " << c2 << " are EQUAL" << std::endl;
    else
        std::cout << c1 << " and " << c2 << " are NOT EQUAL" << std::endl;

    return 0;
}
/*
 * File: D1_E2_Exercise.cpp
 *
 * Purpose: Implement function to check whether the divisor is zero or not.
 *
 * Author: Varad Lanke
 *
 * Date: March 27, 2026
 *
 * Compilation: g++ D1_E2_Exercise.cpp -o d1_e2.out
 * Execution: ./d1_e2.out
 */

#include <iostream>

template<typename T>
class Calculator
{
    private:
        T divisor;

    public:
        Calculator(T _divisor): divisor(_divisor) { std::cout << "Calculator()" << std::endl; }

        bool isDivisorZero() const
        {
            float epsilon = 0.000000000001; // 1e-11f

            if(std::abs(divisor) < epsilon) return true;

            return false;
        }

        friend std::ostream& operator<<(std::ostream& out, const Calculator& other)
        {
            if(other.isDivisorZero())
                out << "[WARN] Divisor: " << other.divisor << " is ZERO!!";
            else
                out << "[INFO] Divisor: " << other.divisor << " is Non-Zero";
                
            return out;
        }

        Calculator& operator=(float f_num)
        {
            divisor = f_num;
            return *this;
        }

        ~Calculator() { std::cout << "~Calculator()" << std::endl; }

};

int main()
{
    // local variables
    float f_num = 1.1f;
    Calculator<float> c1(f_num);

    std::cout << c1 << std::endl;

    // test case 2
    c1 = 0.0000000000001f; // will considered as 0
    std::cout << c1 << std::endl;

    // test case 3
    c1 = 11;
    std::cout << c1 << std::endl;

    return 0;
}
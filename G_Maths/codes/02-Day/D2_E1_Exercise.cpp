/**
 * File : D2_E1_Exercise.cpp
 * Pupose: To calculate the roots of the Quadratic Equation
 * Author: Varad Lanke
 * Date: March 30, 2026
 * Compilation: g++ D2_E1_Exercise.cpp -o app
 * Exeution: ./app
 */

#include <iostream>
#include <vector>
#include <cmath>

/**
 * Requirement: This function should take coefficients a, b, and c and return the roots. Remember to handle the discriminant (D=b^2−4ac):
 *              - D>0: Two real roots (the ray enters and exits the sphere).
 *              - D=0: One real root (the ray is tangent to the sphere).
 *              - D<0: No real roots (the ray misses the sphere).
 * 
 *              Example: 2x^2 − 4x − 6 = 0
 *                      a = 2, b = -4, c = -6
 *                      D = (−4)^2 − 4*(2)*(−6) = 16 + 48 = 64
 *                      Roots : x = 3 and x = -1
 */
template <typename T = double>
auto SolveQuadratic = [](T a, T b, T c) -> std::pair<T, T> {
                        std::pair<T, T> res;
                        T D = (b*b)-(4* a * c);
                        if(D > 0)
                            std::cout << "[INFO] Two real roots (the ray enters and exits the sphere)." << std::endl;
                        else if(D == 0)
                            std::cout << "[INFO] One real root (the ray is tangent to the sphere)." << std::endl;
                        else
                            std::cout << "[INFO] No real roots (the ray misses the sphere). | two complex number roots" << std::endl;

                        if(std::abs(a) == 0.0f)
                        {
                            std::cerr << "[ERROR] Cannot divide by ZERO!" << std::endl;
                            return res;
                        }

                        T plusRoot = (-b + sqrt(D)) / (2*a);
                        T minusRoot = (-b - sqrt(D)) / (2*a);

                        res.first = plusRoot;
                        res.second = minusRoot;

                        return res;
                    };


int main()
{
    auto res = SolveQuadratic<double>(2.0, -4.0, -6.0);

    std::cout << "Root_1: " << res.first << std::endl
              << "Root_2: " << res.second << std::endl;

    return 0;
}
#include <test.hpp>

/**
 * File: main.cpp
 * Purpose: Entry point for this project
 * Author: Varad Lanke
 * Date: April 20, 2026
 * Compilation: g++ -std=c++17 -I./include/gmath/ -I./tests/ src/main.cpp -o build/app
 * Execution: ./build/app
 */

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

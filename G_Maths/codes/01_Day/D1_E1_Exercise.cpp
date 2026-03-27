/*
 * File: D1_E1_Exercise.cpp
 *
 * Purpose: Implement functions to compute the square and cube of a given number.
 *
 * Author: Varad Lanke
 *
 * Date: March 27, 2026
 *
 * Compilation: g++ D1_E1_Exercise.cpp -o d1_e1.out
 * Execution: ./d1_e1.out
 */

#include <iostream>

template<typename T>
class Calculator
{
	private:
		T number;

	public:
		explicit Calculator(T _number): number(_number) { std::cout << "[INFO] Calculator()" << std::endl; };

		T getSquare() const { return number * number; };

		T getCube() const { return number * number * number; };

		friend std::ostream& operator<<(std::ostream& out, const Calculator& other)
		{
			out << "[INFO] Square of " << other.number << " is: " << other.getSquare()
				<< " | Cube of " << other.number << " is: " << other.getCube();
			return out;
		}

		~Calculator() { std::cout << "[INFO] ~Calculator()" << std::endl; };
};

int main()
{
	// local variables
	float x = 1.1f;
	Calculator<float> c1(1.1f);

	std::cout << c1 << std::endl;

	return 0;
}
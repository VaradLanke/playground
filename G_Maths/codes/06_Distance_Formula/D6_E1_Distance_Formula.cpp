/**
 * File: D6_E1_Distance_Formula.cpp
 * Purpose: To implement the distance formula
 * Author: Varad Lanke
 * Date: April 14, 2026
 * Compilation: g++ D6_E1_Distance_Formula.cpp -o app
 * Execution: ./app
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>
//#include <typeinfo>
#include <stdexcept>

namespace gm // graphics math
{
    template <typename T = float>
    struct Point
    {
        T x;
        T y;
        T z;
        Point() : x((T)0), y((T)0), z((T)0) {}

        explicit Point(std::initializer_list<T> list)
        {
            if(list.size() != 3)
            {
                throw std::invalid_argument("[ERROR] Point requires 3 co-ordinates");
            }

            typename std::initializer_list<T>::iterator it = list.begin();
            //std::cout << "type: " << typeid(it).name() << "\n";
            x = *it++;
            y = *it++;
            z = *it;
        }

        friend std::ostream& operator<<(std::ostream& out, const Point& other)
        {
            out << "(" << other.x << "," << other.y << "," << other.z << ")";
            return out;
        }
    };

    template<typename T>
    class Calculator
    {
        public:
            Calculator() = default;
            
            /** 
             * Distance Formula
             * dist = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1))
            */
            T getDistance(const Point<T>& pt1, const Point<T>& pt2)
            {
                return std::sqrt(Square(pt2.x - pt1.x) +
                                    Square(pt2.y - pt1.y) +
                                    Square(pt2.z - pt1.z));
            }

            const std::function<T(T)> Square = [](T number) -> T { return number * number; };
    };
};

//----------------------- Test Cases --------------------------------------------------

namespace test
{
    void test_valid()
    {
        gm::Calculator<double> c1;
        gm::Point<double> p1{2.0, 5.0, 3.0};
        gm::Point<double> p2{3.2, 7.1, 6.8};
        auto res = c1.getDistance(p1, p2);

        std::cout << "[INFO]: Distance : d(P2"<< p2 << ",P1" << p1 << ") = " << res << std::endl;
    }

    void test_negative()
    {
        gm::Calculator<double> c1;
        gm::Point<double> p1{2.0, 5.0, 3.0};
        gm::Point<double> p2{-3.2, -7.1, -6.8};
        auto res = c1.getDistance(p1, p2);

        std::cout << "[INFO]: Distance : d(P2"<< p2 << ",P1" << p1 << ") = " << res << std::endl;
    }

    void test_self()
    {
        gm::Calculator<double> c1;
        gm::Point<double> p1{2.0, 5.0, 3.0};
        gm::Point<double> p2{2.0, 5.0, 3.0};
        auto res = c1.getDistance(p1, p2);

        std::cout << "[INFO]: Distance : d(P2"<< p2 << ",P1" << p1 << ") = " << res << std::endl;
    }
}


//-------------------- Entry Point function ---------------------------------------------

int main()
{
    try
    {
        std::cout << std::fixed << std::setprecision(6);

        std::cout << std::endl << "[INFO] ---- Test Case : Valid ----" << std::endl;
        test::test_valid();

        std::cout << std::endl << "[INFO] ---- Test Case : Negative Co-ordinates ----" << std::endl;
        test::test_negative();

        std::cout << std::endl << "[INFO] ---- Test Case : Same Point (Zero Distance) ----" << std::endl;
        test::test_self();
    } catch(const std::exception& e)
    {
        std::cerr << "[ERROR]: " << e.what() << std::endl;
    }

    return 0;
}
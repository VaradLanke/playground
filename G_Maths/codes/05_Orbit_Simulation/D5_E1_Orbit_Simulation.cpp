/**
 * File: D5_E1_Orbit_Simulation.cpp
 * Purpose: To simulate the circular motion in the orbit by printing orbital points
 * Author: Varad Lanke
 * Date: April 11, 2026
 * Compilation: g++ D5_E1_Orbit_Simulation.cpp -o app
 * Execution: ./app
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

template<typename T>
constexpr T PI = (T)3.14159265358979323846;

template<typename T>
class Orbit
{
    private:
        const T radius;
        std::vector<std::pair<T, T>> orbitPath;

    public:
        Orbit(T _radius = 1.0) : radius(_radius) {}

        constexpr void fillOrbitPath(const T incr_val) noexcept
        {
            for(T angle = 0.0; angle <= 360.0; angle += incr_val)
            {
                T xPoint = radius * std::cos(getRadians(angle));
                T yPoint = radius * std::sin(getRadians(angle));
                std::pair<T, T> pt(xPoint, yPoint);
                orbitPath.push_back(pt);
            }
        }

        constexpr T getRadians(T angle) const { return (angle * (PI<T>/180.0)); }

        constexpr friend std::ostream& operator<<(std::ostream& out, Orbit& other)
        {
            out << "Points: ";
            for(typename std::vector<std::pair<T, T> >::iterator it = other.orbitPath.begin();
                it != other.orbitPath.end();
                ++it)
                {
                    out << "(" << (*it).first << "," << (*it).second << ")";
                }
            return out;
        }
};



int main()
{
    Orbit<double> o1(1.0);
    o1.fillOrbitPath(90.0);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "[INFO]: " << o1 << std::endl;

    return 0;
}

/**
 * File: D4_E1_Exercise.cpp
 * Purpose: Trigonometry & Foundations
 * Author: Varad Lanke
 * Date: April 8, 2026
 * Compilation: g++ D4_E1_Exercise.cpp -o app
 */

#include <iostream>
#include <iomanip>
#include <cmath>

constexpr double PI = 3.14159265359;

template <typename T>
class Point
{
    public:
        T x;
        T y;
        T z;

        Point() = default;
        Point(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};

        Point(const Point<T>& other)
        {
            std::cout << "[INFO] copy ctor operator called..." << std::endl;
            x = other.x;
            y = other.y;
            z = other.z;
        }

        Point(const Point<T>&& other)
        {
            std::cout << "[INFO] move ctor operator called..." << std::endl;
            x = other.x;
            y = other.y;
            z = other.z;
        }

        Point<T>& operator=(const Point<T>& other)
        {
            //std::cout << "[INFO] copy = operator called..." << std::endl;
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        Point<T>& operator=(const Point<T>&& other)
        {
            //std::cout << "[INFO] move = operator called..." << std::endl;
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, const Point<T>& other)
        {
            out << "Point: (" << other.x << ", " << other.y << ", " << other.z << ")";
            return out;
        }
};

template<typename T>
class Trigonometry
{
    private:
        T angleInRadians;
        Point<T> pt;
    public:
        Trigonometry(T _angle, Point<T> _pt) : angleInRadians(_angle), pt(std::move(_pt))
        {
            std::cout << "[INTO] Trigonometry()" << std::endl;
        }

        constexpr T toRadians(T inAngle) const { return (inAngle * (PI / 180.0f)); }

        constexpr T toDegrees(T inAngle) const { return (inAngle * (180.0f / PI)); }

        constexpr T getAngleInRadians() const { return angleInRadians; }

        Point<T>& rotateAntiClockWise(Point<T>& _pt, T angle)
        {
            T x = _pt.x;
            T y = _pt.y;
            _pt.x = (x * std::cos(angle)) - (y * std::sin(angle));
            _pt.y = (x * std::sin(angle)) + (y * std::cos(angle));
            return _pt;
        }

        ~Trigonometry() { std::cout << "[INTO] ~Trigonometry()" << std::endl; }

        friend std::ostream& operator<<(std::ostream& out, const Trigonometry& other)
        {
            out << "[INFO] angleInRadians: " << other.angleInRadians
                << " | angleInDegrees: " << other.toDegrees(other.angleInRadians);
            return out;
        }
};

int main()
{
    constexpr double testAngleRad = 2 * PI;
    constexpr double testAngleDeg = 360.0;

    Point<double> pt1(0.0f, 1.0f, 0.0f);

    std::cout << "[INFO] pt1: " << pt1 << std::endl;

    Trigonometry<double> t1(testAngleRad, pt1);

    std::cout << std::fixed << std::setprecision(11);
    std::cout << "[INFO] PI: " << PI << std::endl;

    std::cout << t1 << std::endl;
    std::cout << "[INFO] Angle in Radians: " << t1.toRadians(testAngleDeg) << std::endl;

    t1.rotateAntiClockWise(pt1, testAngleRad/2);
    std::cout << "After Rotation: " << std::endl;
    std::cout << "[INFO] pt1: " << pt1 << std::endl;

    return 0;
}

void testPoint()
{
    Point<double> pt1(0.0f, 1.0f, 0.0f);
    Point<double> pt2(1.1f, 2.2f, 3.3f);
    Point<double> pt3(pt1);
    Point<double> pt4(std::move(pt2));

    std::cout << "[INFO] pt1: " << pt1 << std::endl;
    pt1 = pt2;

    std::cout << "[INFO] pt2: " << pt2 << std::endl;
    pt2 = std::move(pt1);

    std::cout << "[INFO] pt1: " << pt1 << std::endl;
    std::cout << "[INFO] pt2: " << pt2 << std::endl;
}
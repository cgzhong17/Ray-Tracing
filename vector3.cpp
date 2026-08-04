#include <vector3.hpp>
#include <vector>
#include <cmath>

using namespace std;

Vector3 :: Vector3() : x{0.0}, y{0.0}, z{0.0} {};

Vector3 :: Vector3(double x, double y, double z) : x{x}, y{y}, z{z} {};

Vector3 PhysicalObjects :: getPosition() const{
    return position;
}

PhysicalObjects :: PhysicalObjects(Vector3 position, shared_ptr<Color> color_ptr) : position{position}, color{color_ptr} {};

shared_ptr<Color> PhysicalObjects :: getColor() const{
    return color;
}

Color :: Color() : r{0.0}, g{0.0}, b{0.0} {};

Color :: Color(double r, double g, double b) : r{r}, g{g}, b{b} {};

double Sphere :: shape() const{
    return (4.0/3.0) * PI * pow(radius, 3);
}

double Cube :: shape() const{
    return length * width * height;
}



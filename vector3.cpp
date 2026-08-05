#include "vector3.hpp"
#include <vector>
#include <cmath>

using namespace std;

Vector3 :: Vector3() : x{0.0}, y{0.0}, z{0.0} {}

Vector3 :: Vector3(double x, double y, double z) : x{x}, y{y}, z{z} {}

double Vector3 :: getX() const{
    return x;
}

double Vector3 :: getY() const{
    return y;
}

double Vector3 :: getZ() const{
    return z;
}

Vector3 Vector3 :: operator-(const Vector3& other) const{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3 :: operator+(const Vector3& other) const{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3 :: operator*(double scaler) const{
    return Vector3(x * scaler, y * scaler, z * scaler);
}

double Vector3 :: dot(const Vector3& other) const{
    return x*other.x + y*other.y + z*other.z;
}

double Vector3 :: length() const{
    return sqrt(x*x + y*y + z*z);
}

Vector3 Vector3 :: normalized() const{
    double len = this->length();
    return Vector3(x / len, y / len, z / len);
}

Vector3 PhysicalObjects :: getPosition() const{
    return position;
}

PhysicalObjects :: PhysicalObjects(Vector3 position, shared_ptr<Color> color_ptr) : position{position}, color{color_ptr} {}

shared_ptr<Color> PhysicalObjects :: getColor() const{
    return color;
}

Color :: Color() : r{0.0}, g{0.0}, b{0.0} {}

Color :: Color(double r, double g, double b) : r{r}, g{g}, b{b} {}

Sphere :: Sphere(Vector3 position, std :: shared_ptr<Color> color, double radius) : PhysicalObjects{position, color}, radius{radius} {}

double Sphere :: shape() const{
    return (4.0/3.0) * PI * pow(radius, 3);
}

Cube :: Cube(Vector3 position, std :: shared_ptr<Color> color, double length, double width, double height) : PhysicalObjects{position, color}, length{length}, width{width}, height{height} {}

double Cube :: shape() const{
    return length * width * height;
}



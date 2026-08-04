#include <vector>
#include <memory>

constexpr double PI = 3.14159265358979;
class Vector3{
    public:
        Vector3();
        Vector3(double x, double y, double z);

    private:
        double x;
        double y;
        double z;
};

class Color{
    public:
        Color();
        Color(double r, double g, double b);
    private:
        double r;
        double g;
        double b;
};

class PhysicalObjects {
    public:
        PhysicalObjects(Vector3 position, std :: shared_ptr<Color> color);
        virtual double shape() const = 0;
        Vector3 getPosition() const;
        std :: shared_ptr<Color> getColor() const;

    private:
        Vector3 position;
        std :: shared_ptr<Color> color;
};

class Sphere : public PhysicalObjects{
    public:
        double shape() const;

    private:
        double radius;
};

class Cube : public PhysicalObjects {
    public:
        double shape() const;
    private:
        double length;
        double width;
        double height;
};


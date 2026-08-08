#pragma once
#include <vector>
#include <memory>

constexpr double PI = 3.14159265358979;
class Vector3{
    public:
        Vector3();
        Vector3(double x, double y, double z);
        double getX() const;
        double getY() const;
        double getZ() const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator+(const Vector3& other) const;
        Vector3 operator*(double scaler) const;
        double dot(const Vector3& other) const;
        double length() const;
        Vector3 normalized() const;

    private:
        double x;
        double y;
        double z;
};

class Color{
    public:
        Color();
        Color(double r, double g, double b);
        double GetR() const;
        double GetG() const;
        double GetB() const;
    private:
        double r;
        double g;
        double b;
};

class Ray;

class PhysicalObjects {
    public:
        PhysicalObjects(Vector3 position, std :: shared_ptr<Color> color);
        virtual double shape() const = 0;
        Vector3 getPosition() const;
        void setPosition(const Vector3& position);
        std :: shared_ptr<Color> getColor_ptr() const;
        virtual bool isIntersected(const Ray& ray, double& t) const = 0;
        virtual Vector3 getNormal(const Vector3& point) const = 0;

    private:
        Vector3 position;
        std :: shared_ptr<Color> color;
};


class Sphere : public PhysicalObjects{
    public:
        Sphere(Vector3 position, std :: shared_ptr<Color> color, double radius);
        double shape() const;
        bool isIntersected(const Ray& ray, double& t) const override;
        Vector3 getNormal(const Vector3& point) const override;

    private:
        double radius;
};

class Cube : public PhysicalObjects {
    public:
        Cube(Vector3 position, std :: shared_ptr<Color> color, double length, double width, double height);
        double shape() const;
        bool isIntersected(const Ray& ray, double& t) const override;
        Vector3 getNormal(const Vector3& point) const override;

    private:
        double length;
        double width;
        double height;
};


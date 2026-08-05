#include "raytracer.hpp"
#include <cmath>

Ray :: Ray() : origin{0.0, 0.0, 0.0}, direction{0.0, 0.0, 0.0} {}

Ray :: Ray(Vector3 origin, Vector3 direction) : origin{origin}, direction{direction} {}

Vector3 Ray :: getOrigin() const{
    return origin;
}

Vector3 Ray :: getDirection() const{
    return direction;
}

Vector3 Ray :: getPoint(double t) const{
    return origin + direction * t;
}

bool Sphere :: isIntersected(const Ray& ray, double& t) const{
    Vector3 relativePosition = ray.getOrigin() - getPosition();
    Vector3 direction = ray.getDirection();

    double a = direction.dot(direction);
    double b = 2.0 * relativePosition.dot(direction);
    double c = relativePosition.dot(relativePosition) - radius * radius;

    // Calculate existence of solutions b^2 - 4ac
    double intersected_numbers = b * b - 4 * a * c;
    if(intersected_numbers < 0.0)
        return false;

    // Calculate x1, x2 for quadratic equation (-b +- sqrt(b^2 - 4ac)) / 2a
    double intersect_pt1 = (-1.0 * b - sqrt(b * b - 4 * a * c)) / 2.0 * a;
    double intersect_pt2 = (-1.0 * b + sqrt(b * b - 4 * a * c)) / 2.0 * a;

    if(intersect_pt1 > 0){
        t = intersect_pt1;
        return true;
    }

    if(intersect_pt2 > 0){
        t = intersect_pt2;
        return true;
    }
    return false;
}


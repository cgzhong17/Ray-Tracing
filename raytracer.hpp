#include "vector3.hpp"

class Ray{
    public:
        Ray();
        Ray(Vector3 origin, Vector3 direction);
        Vector3 getOrigin() const;
        Vector3 getDirection() const;
        Vector3 getPoint(double t) const;

    private:
        Vector3 origin;
        Vector3 direction;
};


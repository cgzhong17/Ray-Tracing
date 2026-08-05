#include "raytracer.hpp"
#include <memory>
#include <iostream>
using namespace std;

int main(){
    Vector3 sphere_position = Vector3(0.0, 0.0, 2.0);
    auto sphere_color = std::make_shared<Color>(Color(0.0, 0.0, 25.0));

    Sphere sphere = Sphere(sphere_position, sphere_color, 1.0);

    //const Ray ray = Ray(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 1.0));

    for(int w = 0; w < 20; ++w){
        for(int h = 0; h < 40; ++h){
            double t;
            double p = (h - 40.0 / 2.0) / (40.0 / 2.0);
            double y = (w - 20.0 / 2.0) / (20.0 / 2.0);
            const Ray camera_ray = Ray(Vector3(0.0, 0.0, 0.0), Vector3(p, -y, 1.0).normalized());
            if(sphere.isIntersected(camera_ray, t))
                cout << '#';
            else
                cout << ' ';
        }
        cout << endl;
    }
}
#include <SDL2/SDL.h>
#include "raytracer.hpp"
#include <memory>
#include <iostream>
using namespace std;

int main(){
    int width = 1280;
    int height = 720;
    Vector3 sphere_position = Vector3(0.0, 0.0, 2.0);
    auto sphere_color = std::make_shared<Color>(Color(60.0, 60.0, 255.0));

    Sphere sphere = Sphere(sphere_position, sphere_color, 1.0);

    //const Ray ray = Ray(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 1.0));

    /*for(int w = 0; w < 20; ++w){
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
    }*/

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Vector3 light_pos = Vector3(-3.0, 3.0, 0.0);
    for(int h = 0; h < height; ++h){
        for(int w = 0; w < width; ++w){
            double t;
            double x = (w - width / 2.0) / (width / 2.0);
            double y = (h - height / 2.0) / (height / 2.0);
            double aspect = static_cast<double> (width) / height;
            x *= aspect;
            const Ray camera_ray = Ray(Vector3(0.0, 0.0, 0.0), Vector3(x, -y, 1.0).normalized());
            if(sphere.isIntersected(camera_ray, t)){
                Color shading_color = shading(sphere, light_pos, camera_ray, t);
                SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(shading_color.GetR()), static_cast<Uint8>(shading_color.GetG()), static_cast<Uint8>(shading_color.GetB()), 255);
                SDL_RenderDrawPoint(renderer, w, h);
            }
        }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
}
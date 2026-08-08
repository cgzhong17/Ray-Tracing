#include <SDL2/SDL.h>
#include "raytracer.hpp"
#include <memory>
#include <iostream>
#include <vector>
using namespace std;

int main(){
    int width = 1280;
    int height = 720;
    //Vector3 sphere_position = Vector3(0.0, 0.0, 2.0);
    auto sphere_color1 = std::make_shared<Color>(Color(60.0, 60.0, 255.0));
    auto sphere_color2 = std::make_shared<Color>(Color(60.0, 255.0, 60.0));
    //Sphere sphere = Sphere(sphere_position, sphere_color, 1.0);

    //const Ray ray = Ray(Vector3(0.0, 0.0, 0.0), Vector3(0.0, 0.0, 1.0));


    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    bool dragging = false;

    vector<shared_ptr<PhysicalObjects>> objects = {};
    objects.push_back(make_shared<Sphere>(Vector3(2.0, 0.0, 2.0), sphere_color1, 1.0));
    objects.push_back(make_shared<Sphere>(Vector3(-2.0, 0.0, 5.0), sphere_color2, 1.0));
    shared_ptr<PhysicalObjects> selected = nullptr;
    while(running){
        SDL_Event event;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                running = false;
            if(event.type == SDL_MOUSEBUTTONDOWN){
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                double x = (mouse_x - width  / 2.0) / (width  / 2.0);
                double y = (mouse_y - height / 2.0) / (height / 2.0);
                x *= static_cast<double>(width) / height;
                Ray pick_ray(Vector3(0,0,0), Vector3(x, -y, 1.0).normalized());

                double closest_t = std::numeric_limits<double>::max();
                selected = nullptr;
                for(const shared_ptr<PhysicalObjects>& obj : objects){
                    double t;
                    if(obj->isIntersected(pick_ray, t) && t < closest_t){
                        closest_t = t;
                        selected = obj;
                    }
                }
                if(selected)
                    dragging = true;
            }


            if(event.type == SDL_MOUSEBUTTONUP){
                dragging = false;
            }
            if(event.type == SDL_MOUSEMOTION && dragging && selected){
                int mouse_x = event.motion.x;
                int mouse_y = event.motion.y;
                double wx = (mouse_x - width  / 2.0) / (width  / 2.0);
                double wy = (mouse_y - height / 2.0) / (height / 2.0);
                double aspect = static_cast<double>(width) / height;
                wx *= aspect;
                double z = selected -> getPosition().getZ();
                selected -> setPosition(Vector3(wx * z, -wy * z, z));
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        Vector3 light_pos = Vector3(-3.0, 3.0, 0.0);
        for(int h = 0; h < height; ++h){
            for(int w = 0; w < width; ++w){
                double t;
                double x = (w - width / 2.0) / (width / 2.0);
                double y = (h - height / 2.0) / (height / 2.0);
                double aspect = static_cast<double> (width) / height;
                x *= aspect;
                const Ray camera_ray = Ray(Vector3(0.0, 0.0, 0.0), Vector3(x, -y, 1.0).normalized());
                double closest_t = std::numeric_limits<double>::max();
                shared_ptr<PhysicalObjects> hit = nullptr;
                for(const shared_ptr<PhysicalObjects>& obj : objects){
                    if(obj->isIntersected(camera_ray, t) && t < closest_t){
                        closest_t = t;
                        hit = obj;
                    }
                }

                if(hit){
                    Color shading_color = shading(*hit, light_pos, camera_ray, closest_t);
                    SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(shading_color.GetR()), static_cast<Uint8>(shading_color.GetG()), static_cast<Uint8>(shading_color.GetB()), 255);
                    SDL_RenderDrawPoint(renderer, w, h);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }

}
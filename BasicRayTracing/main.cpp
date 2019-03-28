#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"
#include "hitable.h"
#include "sphere.hpp"
#include "hitableList.hpp"
#include "camera.hpp"
#include "lambert.hpp"

const int maxDepth = 10;
const int numberOfSamples = 100;

vec3 getColorForRay(const ray& r, const hitable& world, int depth) {
    hitRecord rec;
    if(depth <  maxDepth && world.hit(r, 0.001, MAXFLOAT, rec)) {
        vec3 atten;
        ray scatted;
        if(rec.mtl->scatter(r, rec, atten, scatted)) {
            return atten * getColorForRay(scatted, world, depth + 1);
        }
        //return (rec.normal + vec3(1, 1, 1)) / 2;
    }
    vec3 unitDir = getUnitVector(r.direction());
    float blend = 0.5 * (unitDir.y() + 1.0);
    vec3 white(1, 1, 1);
    vec3 blue(0.5 * 0.5, 0.7 * 0.7, 1.0);
    return white * (1.0 - blend) + blue * blend;
}
int main(int argc, const char * argv[]) {
    hitableList world;
    world.addHitable(new sphere(vec3(0, 0, -1), 0.5, new lambert(vec3(0.5, 0.8, 0.9))));
    world.addHitable(new sphere(vec3(0, -100.5, -1), 100, new lambert(vec3(0.9, 0.5, 0.5))));
    int nx = 400;
    int ny = 200;
    std::cout<<"P3\n"<< nx << " "<< ny << "\n255\n";
    
    camera cam;
    for (int j = ny - 1 ; j >= 0; --j) {
        for(int i = 0; i < nx; ++i) {
            vec3 color(0, 0, 0);
            for(int s = 0; s < numberOfSamples; ++s) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.getRay(u, v);
                color += getColorForRay(r, world, 0);
            }
            color /= numberOfSamples;
            color = vec3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));
            int ir = int(color.r() * 255.99);
            int ig = int(color.g() * 255.99);
            int ib = int(color.b() * 255.99);
            std::cout<< ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}

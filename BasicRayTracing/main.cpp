#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"
#include "hitable.h"
#include "sphere.hpp"
#include "hitableList.hpp"
#include "camera.hpp"
#include "lambert.hpp"
#include "metal.hpp"
#include "dielectric.hpp"

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

hitable* random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambert(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    const int repeat = 11;
    for (int a = -repeat; a < repeat; a++) {
        for (int b = -repeat; b < repeat; b++) {
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(center, 0.2, new lambert(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(center, 0.2,
                                           new metal(vec3(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())),  0.5*drand48()));
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }
    
    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambert(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    
    hitableList* scene = new hitableList();
    for(int j = 0; j < i; ++j) {
        scene->addHitable(list[j]);
    }
    return scene;
    
}
hitable* staticScene() {
    hitableList* pWorld = new hitableList();
    pWorld->addHitable(new sphere(vec3(0, 0, -1), 0.5, new lambert(vec3(0.1, 0.2, 0.5))));
    pWorld->addHitable(new sphere(vec3(0, -100.5, -1), 100, new lambert(vec3(0.8, 0.8, 0.0))));
    pWorld->addHitable(new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.01)));
    pWorld->addHitable(new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5)));
    pWorld->addHitable(new sphere(vec3(-1, 0, -1), -0.2, new dielectric(1.5)));
    return pWorld;
}
int main(int argc, const char * argv[]) {

    hitable* pWorld = random_scene();
    int nx = 900;
    int ny = 600;
    std::cout<<"P3\n"<< nx << " "<< ny << "\n255\n";
    vec3 eye(13, 2, 3);
    vec3 focus(0, 0, 0);
    float focusDist = 10;
    float aperture = 0.0;
    camera cam(eye, focus, vec3(0, 1, 0), 40, float(nx)/ny, aperture, focusDist);
    for (int j = ny - 1 ; j >= 0; --j) {
        for(int i = 0; i < nx; ++i) {
            vec3 color(0, 0, 0);
            for(int s = 0; s < numberOfSamples; ++s) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.getRay(u, v);
                color += getColorForRay(r, *pWorld, 0);
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

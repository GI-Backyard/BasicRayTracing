#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"
#include "hitable.h"
#include "sphere.hpp"
#include "movingSphere.hpp"
#include "hitableList.hpp"
#include "camera.hpp"
#include "lambert.hpp"
#include "metal.hpp"
#include "dielectric.hpp"
#include "bvhNode.hpp"

const int maxDepth = 10;
const int numberOfSamples = 100;

Vec3 getColorForRay(const Ray& r, const Hitable& world, int depth) {
    HitRecord rec;
    if(depth <  maxDepth && world.hit(r, 0.001, MAXFLOAT, rec)) {
        Vec3 atten;
        Ray scatted;
        if(rec.mtl->scatter(r, rec, atten, scatted)) {
            return atten * getColorForRay(scatted, world, depth + 1);
        }
        //return (rec.normal + vec3(1, 1, 1)) / 2;
    }
    Vec3 unitDir = getUnitVector(r.direction());
    float blend = 0.5 * (unitDir.y() + 1.0);
    Vec3 white(1, 1, 1);
    Vec3 blue(0.5 * 0.5, 0.7 * 0.7, 1.0);
    return white * (1.0 - blend) + blue * blend;
}

Hitable* random_scene() {
    int n = 500;
    Hitable **list = new Hitable*[n+1];
    list[0] =  new Sphere(Vec3(0,-1000,0), 1000, new Lambert(Vec3(0.5, 0.5, 0.5)));
    int i = 1;
    const int repeat = 11;
    for (int a = -repeat; a < repeat; a++) {
        for (int b = -repeat; b < repeat; b++) {
            float choose_mat = drand48();
            Vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if ((center-Vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new Sphere(center, 0.2, new Lambert(Vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new Sphere(center, 0.2,
                                           new Metal(Vec3(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())),  0.5*drand48()));
                }
                else {  // glass
                    list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
                }
            }
        }
    }
    
//    list[i++] = new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5));
//    list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new Lambert(Vec3(0.4, 0.2, 0.1)));
//    list[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.0));

    list[i++] = new MovingSphere(Vec3(0, 1, 0), Vec3(0, 1.2, 0), 0.0, 1.0, 1.0, new Dielectric(1.5));
    list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new Lambert(Vec3(0.4, 0.2, 0.1)));
    list[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.0));

    HitableList* scene = new HitableList();
    for(int j = 0; j < i; ++j) {
        scene->addHitable(list[j]);
    }
//#define USE_BVH
#ifdef USE_BVH
    std::vector<Hitable*> sceneNodes = scene->hitables;
    BVHNode* node = new BVHNode(&sceneNodes[0], sceneNodes.size(), 0.0, 1.0f);
    return node;
#else
    return scene;
#endif
    
}
Hitable* staticScene() {
    HitableList* pWorld = new HitableList();
    pWorld->addHitable(new Sphere(Vec3(0, 0, -1), 0.5, new Lambert(Vec3(0.1, 0.2, 0.5))));
    pWorld->addHitable(new Sphere(Vec3(0, -100.5, -1), 100, new Lambert(Vec3(0.8, 0.8, 0.0))));
    pWorld->addHitable(new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.01)));
    pWorld->addHitable(new Sphere(Vec3(-1, 0, -1), 0.5, new Dielectric(1.5)));
    pWorld->addHitable(new Sphere(Vec3(-1, 0, -1), -0.2, new Dielectric(1.5)));
    return pWorld;
}
int main(int argc, const char * argv[]) {

    Hitable* pWorld = random_scene();
    int nx = 600;
    int ny = 400;
    std::cout<<"P3\n"<< nx << " "<< ny << "\n255\n";
    Vec3 eye(13, 2, 3);
    Vec3 focus(0, 0, 0);
    float focusDist = 10;
    float aperture = 0.0;
    Camera cam(eye, focus, Vec3(0, 1, 0), 40, float(nx)/ny, aperture, focusDist, 0.0f, 0.2f);
    for (int j = ny - 1 ; j >= 0; --j) {
        for(int i = 0; i < nx; ++i) {
            Vec3 color(0, 0, 0);
            for(int s = 0; s < numberOfSamples; ++s) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                Ray r = cam.getRay(u, v);
                color += getColorForRay(r, *pWorld, 0);
            }
            color /= numberOfSamples;
            color = Vec3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));
            int ir = int(color.r() * 255.99);
            int ig = int(color.g() * 255.99);
            int ib = int(color.b() * 255.99);
            std::cout<< ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}

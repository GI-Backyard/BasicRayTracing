#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"
#include "hitable.hpp"
#include "sphere.hpp"
#include "movingSphere.hpp"
#include "hitableList.hpp"
#include "camera.hpp"
#include "bvhNode.hpp"
#include "texture.hpp"

const int maxDepth = 10;
const int numberOfSamples = 100;

Vec3 getColorForRay(const Ray& r, const Hitable& world, int depth) {
    HitRecord rec;
    if(world.hit(r, 0.001, MAXFLOAT, rec)) {
        Vec3 atten;
        Ray scatted;
        Vec3 emitted = rec.mtl->emitted(rec.u, rec.v, rec.p);
        if(depth <  maxDepth && rec.mtl->scatter(r, rec, atten, scatted)) {
            return emitted + atten * getColorForRay(scatted, world, depth + 1);
        } else {
            return emitted;
        }
        //return (rec.normal + vec3(1, 1, 1)) / 2;
    }
    
    return Vec3(0, 0, 0);
//    Vec3 unitDir = getUnitVector(r.direction());
//    float blend = 0.5 * (unitDir.y() + 1.0);
//    Vec3 white(1, 1, 1);
//    Vec3 blue(0.5 * 0.5, 0.7 * 0.7, 1.0);
//    return white * (1.0 - blend) + blue * blend;
}

Hitable* random_scene() {
    int n = 500;
    Hitable **list = new Hitable*[n+1];
    Texture* p1 = new ConstantTexture(Vec3(0.5, 0.5, 0.5));
    Texture* p2 = new ConstantTexture(Vec3(0.8, 0.8, 0.8));
    list[0] =  new Sphere(Vec3(0,-1000,0), 1000, new Lambert(new CheckerTexture(p1, p2)));
    int i = 1;
    const int repeat = 11;
    for (int a = -repeat; a < repeat; a++) {
        for (int b = -repeat; b < repeat; b++) {
            float choose_mat = drand48();
            Vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if ((center-Vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    Vec3 color(drand48()*drand48(), drand48()*drand48(), drand48()*drand48());
                    list[i++] = new Sphere(center, 0.2, new Lambert(new ConstantTexture(color)));
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
    Vec3 color(0.4, 0.2, 0.1);
    list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new Lambert(new ConstantTexture(color)));
    list[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5), 0.0));

    HitableList* scene = new HitableList();
    for(int j = 0; j < i; ++j) {
        scene->addHitable(list[j]);
    }
#define USE_BVH

#ifdef USE_BVH
    std::vector<Hitable*> sceneNodes = scene->hitables;
    BVHNode* node = new BVHNode(&sceneNodes[0], (int)sceneNodes.size(), 0.0, 1.0f);
    return node;
#else
    return scene;
#endif
    
}

Hitable* cornellBox() {
    HitableList* world = new HitableList();
    Material* red = new Lambert(new ConstantTexture(Vec3(0.65, 0.05, 0.05)));
    Material* white = new Lambert(new ConstantTexture(Vec3(0.73, 0.73, 0.73)));
    Material* green = new Lambert(new ConstantTexture(Vec3(0.12, 0.45, 0.15)));
    Material* light = new DiffuseLight(new ConstantTexture(Vec3(15, 15, 15)));
    world->addHitable(new FlipNormal(new RectYZ(0, 555, 0, 555, 555, green)));
    world->addHitable(new RectYZ(0, 555, 0, 555, 0, red));
    world->addHitable(new RectXZ(213, 343, 227, 332, 554, light));
    world->addHitable(new FlipNormal(new RectXZ(0, 555, 0, 555, 555, white)));
    world->addHitable(new RectXZ(0, 555, 0, 555, 0, white));
    world->addHitable(new FlipNormal(new RectXY(0, 555, 0, 555, 555, white)));
    return world;
}

Hitable* simpleLight() {
    Texture* perlinTex = new NoiseTexture(4);
    Texture* constTex = new ConstantTexture(Vec3(4, 4, 4));
    HitableList* world = new HitableList();
    world->addHitable(new Sphere(Vec3(0, -1000, 0), 1000, new Lambert(perlinTex)));
    world->addHitable(new Sphere(Vec3(0, 2, 0), 2, new Lambert(perlinTex)));
    world->addHitable(new Sphere(Vec3(0, 7, 0), 2, new DiffuseLight(constTex)));
    world->addHitable(new RectXY(3, 5, 1, 3, -2, new DiffuseLight(constTex)));
    return world;
}

Hitable* twoPerlinSpheres() {
    Texture* perTex = new NoiseTexture(4);
    HitableList* world = new HitableList();
    world->addHitable(new Sphere(Vec3(0, -1000, 0), 1000, new Lambert(perTex)));
    world->addHitable(new Sphere(Vec3(0, 2, 0), 2, new Lambert(perTex)));
    return world;
}

Hitable* staticScene() {
    HitableList* pWorld = new HitableList();
    pWorld->addHitable(new Sphere(Vec3(0, 0, -1), 0.5, new Lambert(new ConstantTexture(Vec3(0.1, 0.2, 0.5)))));
    Vec3 color(0.8, 0.8, 0.0);
    pWorld->addHitable(new Sphere(Vec3(0, -100.5, -1), 100, new Lambert(new ConstantTexture(color))));
    pWorld->addHitable(new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.01)));
    pWorld->addHitable(new Sphere(Vec3(-1, 0, -1), 0.5, new Dielectric(1.5)));
    pWorld->addHitable(new Sphere(Vec3(-1, 0, -1), -0.2, new Dielectric(1.5)));
    return pWorld;
}

Camera basicCamera(int nx, int ny) {
    Vec3 eye(13, 2, 3);
    Vec3 focus(0, 0, 0);
    float focusDist = 10;
    float aperture = 0.0;
    return Camera(eye, focus, Vec3(0, 1, 0), 40, float(nx)/ny, aperture, focusDist, 0.0f, 0.2f);
}

Camera cornellCamera(int nx, int ny) {
    Vec3 eye(278, 278, -800);
    Vec3 focus(278, 278, 0);
    float focusDist = 10;
    float aperture = 0.0;
    return Camera(eye, focus, Vec3(0, 1, 0), 40, float(nx)/ny, aperture, focusDist, 0.0f, 0.2f);
}

int main(int argc, const char * argv[]) {

    Hitable* pWorld = simpleLight();
    pWorld = cornellBox();
    int nx = 900;
    int ny = 600;
    std::cout<<"P3\n"<< nx << " "<< ny << "\n255\n";
    Camera cam = basicCamera(nx, ny);
    cam = cornellCamera(nx, ny);
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

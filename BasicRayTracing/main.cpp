#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"

vec3 getColorForRay(const ray& r) {
    vec3 unitDir = getUnitVector(r.direction());
    float t = 0.5 * (unitDir.y() + 1.0);
    vec3 white(1, 1, 1);
    vec3 blue(0.5, 0.7, 1.0);
    return white * (1.0 - t) + blue * t;
}
int main(int argc, const char * argv[]) {
    int nx = 400;
    int ny = 200;
    std::cout<<"P3\n"<< nx << " "<< ny << "\n255\n";
    vec3 lowLeftCorner( -2, -1, -1);
    vec3 horizontal(4, 0, 0);
    vec3 vertical(0, 2, 0);
    vec3 origin(0, 0, 0);
    for (int j = ny - 1 ; j >= 0; --j) {
        for(int i = 0; i < nx; ++i) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, u * horizontal + v * vertical + lowLeftCorner);
            vec3 color = getColorForRay(r);
            int ir = int(color.r() * 255.99);
            int ig = int(color.g() * 255.99);
            int ib = int(color.b() * 255.99);
            std::cout<< ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}
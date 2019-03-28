
#ifndef ray_hpp
#define ray_hpp

#include "vec3.hpp"
class ray {
public:
    vec3 ori;
    vec3 dir;
public:
    ray() {
        ori = vec3(0 ,0 ,0); dir = vec3(0 ,0 , -1);
    }
    
    ray(const vec3& a, const vec3& b) {
        ori = a; dir = b;
    }
    
    const vec3& origin() const { return ori; }
    const vec3& direction() const { return dir; }
    
    vec3 getPoint(float t) const { return ori + dir * t; }
};

#endif /* ray_hpp */


#ifndef ray_hpp
#define ray_hpp

#include "vec3.hpp"
class Ray {
public:
    Vec3 ori;
    Vec3 dir;
    float _time;
public:
    float time() const { return _time; }
    Ray() {
        ori = Vec3(0 ,0 ,0); dir = Vec3(0 ,0 , -1);
        _time = 0.0f;
    }
    
    Ray(const Vec3& a, const Vec3& b, float ti = 0.0f) {
        ori = a; dir = b;
        _time = ti;
    }
    
    const Vec3& origin() const { return ori; }
    const Vec3& direction() const { return dir; }
    
    Vec3 getPoint(float t) const { return ori + dir * t; }
};

#endif /* ray_hpp */

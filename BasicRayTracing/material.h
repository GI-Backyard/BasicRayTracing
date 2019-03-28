//
//  material.h
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef material_h
#define material_h
#include "ray.hpp"
#include "hitable.h"

class material {
public:
    virtual ~material() {}
    virtual bool scatter(const ray& rIn, const hitRecord& rec, vec3& atten, ray& scatted) const = 0;
    
    static inline vec3 randomInUnitSphere();
    static inline vec3 reflect(const vec3& in, const vec3& normal);
    static inline bool refact(const vec3& vIn, const vec3& n, float niOverNt, vec3& refracted);
    static inline float schlick(float cosine, float refIdx);
};

inline vec3 material::randomInUnitSphere(){
    vec3 p;
    do {
        p = 2 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while(p.squareLength() >= 1.0);
    
    return p;
}

inline vec3 material::reflect(const vec3& in, const vec3& normal) {
    return in + 2 * dot((-normal), in) * normal;
}

inline bool material::refact(const vec3& vIn, const vec3& n, float niOverNt, vec3& refracted) {
    vec3 uv = getUnitVector(vIn);
    float dt = dot(uv, -n);
    float discriminant = 1 - niOverNt * niOverNt * (1 - dt * dt);
    if(discriminant > 0) {
        refracted = (-n) * sqrt(discriminant);
        refracted += niOverNt * (uv - dt * (-n));
        return true;
    } else {
        return false;
    }
}

inline float material::schlick(float cosine, float refIdx) {
    float r0 = (1 - refIdx) / ( 1 + refIdx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1- cosine), 5);
}

#endif /* material_h */

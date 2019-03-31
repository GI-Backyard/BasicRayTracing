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

class Material {
public:
    virtual ~Material() {}
    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const = 0;
    
    static inline Vec3 randomInUnitSphere();
    static inline Vec3 reflect(const Vec3& in, const Vec3& normal);
    static inline bool refract(const Vec3& vIn, const Vec3& n, float niOverNt, Vec3& refracted);
    static inline float schlick(float cosine, float refIdx);
};

inline Vec3 Material::randomInUnitSphere(){
    Vec3 p;
    do {
        p = 2 * Vec3(drand48(), drand48(), drand48()) - Vec3(1, 1, 1);
    } while(p.squareLength() >= 1.0);
    
    return p;
}

inline Vec3 Material::reflect(const Vec3& in, const Vec3& normal) {
    return in + 2 * dot((-normal), in) * normal;
}

inline bool Material::refract(const Vec3& vIn, const Vec3& n, float niOverNt, Vec3& refracted) {
    Vec3 uv = getUnitVector(vIn);
    float dt = dot(uv, n);
    float discriminant = 1.0 - niOverNt*niOverNt*(1-dt*dt);
    if (discriminant > 0) {
        refracted = niOverNt*(uv - n*dt) - n*sqrt(discriminant);
        return true;
    }
    else
        return false;
}

inline float Material::schlick(float cosine, float refIdx) {
    float r0 = (1 - refIdx) / ( 1 + refIdx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1- cosine), 5);
}

#endif /* material_h */

//
//  material.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/4/1.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "material.h"

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

Lambert::Lambert(const Texture* tex)
{
    texture = tex;
}

Lambert::~Lambert() {
    delete texture;
}

bool Lambert::scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const {
    
    atten = texture->value(0, 0, rec.p);
    Vec3 ori = rec.p;
    Vec3 dir = rec.normal + randomInUnitSphere();
    scatted = Ray(ori, dir, rIn.time());
    return true;
}

bool Dielectric::scatter(const Ray& rIn, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const {
    Vec3 outward_normal;
    float ref_idx = refactIndex;
    Vec3 reflected = reflect(rIn.direction(), rec.normal);
    float ni_over_nt;
    attenuation = Vec3(1.0, 1.0, 1.0);
    Vec3 refracted;
    float reflect_prob;
    float cosine;
    if (dot(rIn.direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        //         cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        cosine = dot(rIn.direction(), rec.normal) / rIn.direction().length();
        cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));
    }
    else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(rIn.direction(), rec.normal) / rIn.direction().length();
    }
    if (refract(rIn.direction(), outward_normal, ni_over_nt, refracted))
        reflect_prob = schlick(cosine, ref_idx);
    else
        reflect_prob = 1.0;
    if (drand48() < reflect_prob)
        scattered = Ray(rec.p, reflected, rIn.time());
    else
        scattered = Ray(rec.p, refracted, rIn.time());
    return true;
}

bool Metal::scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const {
    
    atten = albedo;
    Vec3 ori = rec.p;
    Vec3 dir = reflect(rIn.direction(), rec.normal) + fuzzy * randomInUnitSphere();
    scatted = Ray(ori, dir, rIn.time());
    return dot(dir, rec.normal) > 0;
}


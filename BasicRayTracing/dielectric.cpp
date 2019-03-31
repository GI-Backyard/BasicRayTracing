//
//  dielectric.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/29.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "dielectric.hpp"

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


//
//  dielectric.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/29.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "dielectric.hpp"

bool dielectric::scatter(const ray& r_in, const hitRecord& rec, vec3& attenuation, ray& scattered) const {
    vec3 outward_normal;
    float ref_idx = refactIndex;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    float ni_over_nt;
    attenuation = vec3(1.0, 1.0, 1.0);
    vec3 refracted;
    float reflect_prob;
    float cosine;
    if (dot(r_in.direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        //         cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        cosine = dot(r_in.direction(), rec.normal) / r_in.direction().length();
        cosine = sqrt(1 - ref_idx*ref_idx*(1-cosine*cosine));
    }
    else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
        reflect_prob = schlick(cosine, ref_idx);
    else
        reflect_prob = 1.0;
    if (drand48() < reflect_prob)
        scattered = ray(rec.p, reflected);
    else
        scattered = ray(rec.p, refracted);
    return true;
}


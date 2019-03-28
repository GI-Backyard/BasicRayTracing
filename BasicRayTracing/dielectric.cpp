//
//  dielectric.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/29.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "dielectric.hpp"

bool dielectric::scatter(const ray& rIn, const hitRecord& rec, vec3& atten, ray& scatted) const {
    vec3 outwardNormal;
    vec3 reflected = reflect(rIn.direction(), rec.normal);
    float niOverNt;
    atten = vec3(1, 1, 1);
    vec3 refracted;
    float reflect_prob;
    float cosine;
    if(dot(rIn.direction(), rec.normal) > 0) {
        outwardNormal = -rec.normal;
        niOverNt = refactIndex;
        cosine = refactIndex * dot(rIn.direction(), rec.normal) / rIn.direction().length();
    } else {
        outwardNormal = rec.normal;
        niOverNt = 1 / refactIndex;
        cosine = - dot(rIn.direction(), rec.normal) / rIn.direction().length();
    }
    
    if(refact(rIn.direction(), outwardNormal, niOverNt, refracted)) {
        reflect_prob = schlick(cosine, refactIndex);
    } else {
        scatted = ray(rec.p, reflected);
        reflect_prob = 1.0;
    }
    
    if(drand48() < reflect_prob) {
        scatted = ray(rec.p, reflected);
    } else {
        scatted = ray(rec.p, refracted);
    }
    return true;
}


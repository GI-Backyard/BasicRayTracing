//
//  metal.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "metal.hpp"

vec3 reflect(const vec3& in, const vec3& normal) {
    return in + 2 * dot((-normal), in) * normal;
}

bool metal::scatter(const ray& rIn, const hitRecord& rec, vec3& atten, ray& scatted) const {
    
    atten = albedo;
    vec3 ori = rec.p;
    vec3 dir = reflect(rIn.direction(), rec.normal) + fuzzy * randomInUnitSphere();
    scatted = ray(ori, dir);
    return dot(dir, rec.normal) > 0;
}


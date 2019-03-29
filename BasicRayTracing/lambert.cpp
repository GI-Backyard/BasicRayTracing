//
//  lambert.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "lambert.hpp"

lambert::lambert(const vec3& col)
{
    albedo = col;
}

bool lambert::scatter(const ray& rIn, const hitRecord& rec, vec3& atten, ray& scatted) const {
    
    atten = albedo;
    vec3 ori = rec.p;
    vec3 dir = rec.normal + randomInUnitSphere();
    scatted = ray(ori, dir);
    return true;
}

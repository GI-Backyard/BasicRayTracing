//
//  lambert.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "lambert.hpp"

Lambert::Lambert(const Vec3& col)
{
    albedo = col;
}

bool Lambert::scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const {
    
    atten = albedo;
    Vec3 ori = rec.p;
    Vec3 dir = rec.normal + randomInUnitSphere();
    scatted = Ray(ori, dir);
    return true;
}

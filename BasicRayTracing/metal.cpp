//
//  metal.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "metal.hpp"

bool Metal::scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const {
    
    atten = albedo;
    Vec3 ori = rec.p;
    Vec3 dir = reflect(rIn.direction(), rec.normal) + fuzzy * randomInUnitSphere();
    scatted = Ray(ori, dir);
    return dot(dir, rec.normal) > 0;
}


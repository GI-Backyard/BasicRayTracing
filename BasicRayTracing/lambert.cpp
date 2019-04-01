//
//  lambert.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "lambert.hpp"

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

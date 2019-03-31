//
//  sphere.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "sphere.hpp"
#include "material.h"

Sphere::~Sphere() {
    delete mtl;
}
bool Sphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
    Vec3 ac = r.origin() - center;
    // a * t *t  + b * t + c = 0;
    float a = dot(r.direction(), r.direction());
    float b = dot(r.direction(), ac);
    float c = dot(ac, ac) - radius * radius;
    float discriminant = b * b - a * c;
    if(discriminant < 0) return false;
    float t1 = (- b - sqrt(discriminant))/ a;
    if(t1 >= tMin && t1 <= tMax) {
        rec.t = t1;
        rec.p = r.getPoint(t1);
        rec.normal = (rec.p - center) / radius;
        rec.mtl = this->mtl;
        return true;
    }
    float t2 = (- b + sqrt(discriminant))/ a;
    if(t2 >= tMin && t2 <= tMax) {
        rec.t = t2;
        rec.p = r.getPoint(t2);
        rec.normal = (rec.p - center) / radius;
        rec.mtl = this->mtl;
        return true;
    }
    
    // exceeds tMin and tMax, return false
    return false;
}

bool Sphere::bounding_box(float t0, float t1, AABB& bb) const {
    bb = AABB(this->center - Vec3(radius, radius, radius), this->center + Vec3(radius, radius, radius));
    return true;
}

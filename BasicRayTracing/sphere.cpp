//
//  sphere.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "sphere.hpp"
#include "ray.hpp"

bool sphere::hit(const ray& r, float tMin, float tMax, hitRecord& rec) {
    vec3 ac = r.origin() - center;
    // a * t *t  + b * t + c = 0;
    float a = dot(r.direction(), r.direction());
    float b = 2 * dot(r.direction(), ac);
    float c = dot(ac, ac) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if(discriminant < 0) return false;
    float t1 = (- b - sqrt(discriminant))/ (2 * a);
    if(t1 >= tMin && t1 <= tMax) {
        rec.t = t1;
        rec.p = r.origin() + t1 * r.direction();
        rec.normal = getUnitVector(rec.p - center);
        return true;
    }
    float t2 = (- b + sqrt(discriminant))/ (2 * a);
    if(t2 >= tMin && t2 <= tMax) {
        rec.t = t2;
        rec.p = r.origin() + t2 * r.direction();
        rec.normal = getUnitVector(rec.p - center);
        return true;
    }
    
    // exceeds tMin and tMax, return false
    return false;
}

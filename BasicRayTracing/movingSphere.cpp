//
//  movingSphere.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/31.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "movingSphere.hpp"
MovingSphere::MovingSphere() {
    center1 = center2 = Vec3(0, 0, 0);
    time1 = time2 = 0.0f;
    radius = 1.0f;
    mtl = nullptr;
}
MovingSphere::MovingSphere(Vec3 c1, Vec3 c2, float t1, float t2, float r, Material* pMtl)
: center1(c1), center2(c2), time1(t1), time2(t2), radius(r), mtl(pMtl) {
    
}

Vec3 MovingSphere::center(float time) const {
    float co = (time - time1) / (time2 - time1);
    co = co < 0 ? 0 : co;
    co = co > 1 ? 1 : co;
    return center1 + co * center2;
}

bool MovingSphere::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
    Vec3 center = this->center(r.time());
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

bool MovingSphere::bounding_box(float t0, float t1, AABB& bb) const {
    bb = AABB(this->center(t0) - Vec3(radius, radius, radius), this->center(t0) + Vec3(radius, radius, radius));
    bb = AABB::surroundingBox(bb, AABB(this->center(t1) - Vec3(radius, radius, radius), this->center(t1) + Vec3(radius, radius, radius)));
    return true;
}

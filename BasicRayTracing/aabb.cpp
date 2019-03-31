//
//  aabb.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/31.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "aabb.hpp"

AABB::AABB() {
    _min = _max = Vec3(0, 0, 0);
}
AABB::AABB(const Vec3& min, const Vec3& max) {
    _min = min;
    _max = max;
}

bool AABB::hit(const Ray& r, float tMin, float tMax) const {
    for( int i = 0; i < 3; ++i) {
        float invD = 1.0f / r.direction()[i];
        float t0 = (min()[i] - r.origin()[i]) * invD;
        float t1 = (max()[i] - r.origin()[i]) * invD;
        if(invD < 0.0f) std::swap(t0, t1);
        tMin = t0 > tMin ? t0 : tMin;
        tMax = t1 < tMax ? t1 : tMax;
        if(tMax <= tMin) return false;
    }
    return true;
}

AABB AABB::surroundingBox(const AABB& box0, const AABB& box1) {
    Vec3 small(ffmin(box0.min().x(), box1.min().x()),
               ffmin(box0.min().y(), box1.min().y()),
               ffmin(box0.min().z(), box1.min().z()));
    
    Vec3 big(ffmax(box0.min().x(), box1.min().x()),
             ffmax(box0.min().y(), box1.min().y()),
             ffmax(box0.min().z(), box1.min().z()));
    
    return AABB(small, big);
}

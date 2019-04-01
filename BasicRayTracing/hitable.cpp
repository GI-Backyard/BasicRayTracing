//
//  hitable.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/4/1.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "material.h"
RectXY::~RectXY() {
    delete mtl;
}

bool RectXY::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
    float t = (k - r.origin().z()) / r.direction().z();
    if(t < tMin || t > tMax) return false;
    float x = r.origin().x() + t * r.direction().x();
    float y = r.origin().y() + t * r.direction().y();
    
    if(x < x0 || x > x1 || y < y0 || y > y1) return false;
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    rec.mtl = mtl;
    rec.p = r.getPoint(t);
    rec.normal = Vec3(0 , 0, 1);
    return true;
}

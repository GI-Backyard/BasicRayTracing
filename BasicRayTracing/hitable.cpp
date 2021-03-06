//
//  hitable.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/4/1.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "material.h"
#include "hitable.hpp"

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

bool RectXZ::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
    float t = (k - r.origin().y()) / r.direction().y();
    if(t < tMin || t > tMax) return false;
    float x = r.origin().x() + t * r.direction().x();
    float z = r.origin().z() + t * r.direction().z();
    
    if(x < x0 || x > x1 || z < z0 || z > z1) return false;
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.mtl = mtl;
    rec.p = r.getPoint(t);
    rec.normal = Vec3(0, 1, 0);
    return true;
}

bool RectYZ::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
    float t = (k - r.origin().x()) / r.direction().x();
    if(t < tMin || t > tMax) return false;
    float y = r.origin().y() + t * r.direction().y();
    float z = r.origin().z() + t * r.direction().z();
    if(y < y0 || y > y1 || z < z0 || z > z1) return false;
    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.mtl = mtl;
    rec.p = r.getPoint(t);
    rec.normal = Vec3(1, 0, 0);
    return true;
}

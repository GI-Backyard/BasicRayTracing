//
//  hitable.h
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef hitable_h
#define hitable_h
#include "ray.hpp"
#include "aabb.hpp"

class Material;
class Hitable;
struct HitRecord {
public:
    HitRecord() {
        t = 0;
        u = v = 0;
        mtl = nullptr;
        obj = nullptr;
    }
    float t;
    Vec3 p;
    Vec3 normal;
    float u;
    float v;
    Material* mtl;
    const Hitable* obj;
};

class Hitable {
public:
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
    virtual bool bounding_box(float t0, float t1, AABB& bb) const = 0;
    virtual ~Hitable() {}
};

class RectXY : public Hitable {
private:
    float x0, x1, y0, y1, k;
    Material* mtl;
public:
    RectXY(float x0, float x1, float y0, float y1, float k, Material* mtl) {
        this->x0 = x0; this->x1 = x1;
        this->y0 = y0; this->y1 = y1;
        this->k = k;
        this->mtl = mtl;
    }
    
    ~RectXY();
    
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const;
    virtual bool bounding_box(float t0, float t1, AABB& bb) const {
        bb = AABB(Vec3(x0, y0, k - 0.0001), Vec3(x1, y1, k + 0.0001));
        return true;
    }
};

#endif /* hitable_h */

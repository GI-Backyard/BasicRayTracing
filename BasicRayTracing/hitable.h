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
class Material;
struct HitRecord {
    float t;
    Vec3 p;
    Vec3 normal;
    Material* mtl;
};

class Hitable {
public:
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
    virtual ~Hitable() {}
};

#endif /* hitable_h */

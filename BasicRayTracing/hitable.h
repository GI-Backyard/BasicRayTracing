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
class material;
struct hitRecord {
    float t;
    vec3 p;
    vec3 normal;
    material* mtl;
};

class hitable {
public:
    virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
    virtual ~hitable() {}
};

#endif /* hitable_h */

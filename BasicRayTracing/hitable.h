//
//  hitable.h
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef hitable_h
#define hitable_h
class ray;
struct hitRecord {
    float t;
    vec3 p;
    vec3 normal;
};

class hitable {
public:
    virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) = 0;
};

#endif /* hitable_h */

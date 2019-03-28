//
//  sphere.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef sphere_hpp
#define sphere_hpp
#include "vec3.hpp"
#include "hitable.h"

class sphere : public hitable {
    vec3 center;
    float radius;
public:
    sphere() { center = vec3(0, 0, 0); radius = 1.0; }
    sphere(const vec3& c, float r) { center = c; radius = r; }
    
    virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) override;
    
};

#endif /* sphere_hpp */
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
private:
    vec3 center;
    float radius;
    material* mtl;
public:
    sphere() { center = vec3(0, 0, 0); radius = 1.0; mtl = nullptr; }
    ~sphere();
    sphere(const vec3& c, float r, material* mtl) { center = c; radius = r; this->mtl = mtl; }
    
    virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const override;
    
};

#endif /* sphere_hpp */

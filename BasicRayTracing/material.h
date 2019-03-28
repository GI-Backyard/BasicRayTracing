//
//  material.h
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef material_h
#define material_h
#include "ray.hpp"
#include "hitable.h"

class material {
public:
    virtual ~material() {}
    virtual bool scatter(const ray& rIn, const hitRecord& rec, vec3& atten, ray& scatted) const = 0;
    
    static inline vec3 randomInUnitSphere();
};

inline vec3 material::randomInUnitSphere(){
    vec3 p;
    do {
        p = 2 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    } while(p.squareLength() >= 1.0);
    
    return p;
}

#endif /* material_h */

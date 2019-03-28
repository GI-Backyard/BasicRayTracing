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
};

#endif /* material_h */

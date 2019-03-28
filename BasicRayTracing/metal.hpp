//
//  metal.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef metal_hpp
#define metal_hpp

#include "material.h"

class metal : public material {
private:
    vec3 albedo;
    float fuzzy;
public:
    metal(const vec3& color, float f = 0) {
        albedo = color;
        if(f > 1) fuzzy = 1;
        else if(f < 0) fuzzy = 0;
        else fuzzy = f;
    }
    
    virtual bool scatter(const ray& rIn, const hitRecord& rec, vec3& atten, ray& scatted) const override;
};

#endif /* metal_hpp */

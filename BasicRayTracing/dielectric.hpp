//
//  dielectric.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/29.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef dielectric_hpp
#define dielectric_hpp
#include "material.h"

class dielectric : public material {
private:
    float refactIndex;
public:
    dielectric(float ri) { refactIndex = ri; }
    virtual bool scatter(const ray& rIn, const hitRecord& rec, vec3& atten, ray& scatted) const override;
};

#endif /* dielectric_hpp */

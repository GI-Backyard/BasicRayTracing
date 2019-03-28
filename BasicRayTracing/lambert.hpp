//
//  lambert.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef lambert_hpp
#define lambert_hpp

#include "material.h"

class lambert : public material {
private:
    vec3 albedo;
public:
    lambert(const vec3& col);
    virtual bool scatter(const ray& rIn, const hitRecord& rec, vec3& atten, ray& scatted) const override;
};

#endif /* lambert_hpp */

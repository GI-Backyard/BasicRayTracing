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

class Dielectric : public Material {
private:
    float refactIndex;
public:
    Dielectric(float ri) { refactIndex = ri; }
    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const override;
};

#endif /* dielectric_hpp */

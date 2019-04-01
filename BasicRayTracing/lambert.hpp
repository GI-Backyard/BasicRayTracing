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
#include "texture.hpp"

class Lambert : public Material {
private:
    const Texture* texture;
public:
    ~Lambert();
    Lambert(const Texture* tex);
    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const override;
};

#endif /* lambert_hpp */

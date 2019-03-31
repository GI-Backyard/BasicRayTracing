//
//  movingSphere.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/31.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef movingSphere_hpp
#define movingSphere_hpp

#include "hitable.h"
#include "material.h"

class MovingSphere : public Hitable{
public:
    Vec3 center1;
    Vec3 center2;
    float time1;
    float time2;
    float radius;
    Material* mtl;
public:
    MovingSphere();
    MovingSphere(Vec3 c1, Vec3 c2, float t1, float t2, float r, Material* pMtl);
    
    Vec3 center(float time) const;
    
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;
    virtual bool bounding_box(float t0, float t1, AABB& bb) const override;
};

#endif /* movingSphere_hpp */


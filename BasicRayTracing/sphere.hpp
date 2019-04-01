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
#include "hitable.hpp"

class Sphere : public Hitable {
private:
    Vec3 center;
    float radius;
    Material* mtl;
public:
    Sphere() { center = Vec3(0, 0, 0); radius = 1.0; mtl = nullptr; }
    ~Sphere();
    Sphere(const Vec3& c, float r, Material* mtl) { center = c; radius = r; this->mtl = mtl; }
    
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;
    virtual bool bounding_box(float t0, float t1, AABB& bb) const override;
    
};

#endif /* sphere_hpp */

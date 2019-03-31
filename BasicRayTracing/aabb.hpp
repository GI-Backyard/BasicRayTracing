//
//  aabb.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/31.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef aabb_hpp
#define aabb_hpp
#include "ray.hpp"

class AABB {
public:
    Vec3 _min;
    Vec3 _max;
public:
    AABB();
    AABB(const Vec3& min, const Vec3& max);
    bool hit(const Ray& r, float tMin, float tMax) const;
    const Vec3& min() const { return _min; }
    const Vec3& max() const { return _max; }
    
    inline static float ffmin(float a, float b) { return a < b ? a : b; }
    inline static float ffmax(float a, float b) { return a < b ? b : a; }
    static AABB surroundingBox(const AABB& box0, const AABB& box1);
};

#endif /* aabb_hpp */

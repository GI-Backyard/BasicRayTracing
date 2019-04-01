//
//  bvhNode.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/31.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef bvhNode_hpp
#define bvhNode_hpp

#include "hitable.hpp"
#include <vector>

class BVHNode : public Hitable {
public:
    Hitable* left;
    Hitable* right;
    AABB box;
public:
    BVHNode(Hitable** ll, int n, float t0, float t1);
    
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;
    virtual bool bounding_box(float t0, float t1, AABB& bb) const override;
};

#endif /* bvhNode_hpp */

//
//  hitableList.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef hitableList_hpp
#define hitableList_hpp
#include <vector>
#include "hitable.hpp"

class HitableList : public Hitable {
public:
    std::vector<Hitable*> hitables;
    
public:
    HitableList() {};
    ~HitableList();
    
    void addHitable(Hitable* a);
    
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;
    virtual bool bounding_box(float t0, float t1, AABB& bb) const override;
};

#endif /* hitableList_hpp */

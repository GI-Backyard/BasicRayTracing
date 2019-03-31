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
#include "hitable.h"

class HitableList : public Hitable {
private:
    std::vector<Hitable*> hitables;
    
public:
    HitableList() {};
    ~HitableList();
    
    void addHitable(Hitable* a);
    
    virtual bool hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const override;
};

#endif /* hitableList_hpp */

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

class hitableList : public hitable {
private:
    std::vector<hitable*> hitables;
    
public:
    hitableList() {};
    ~hitableList();
    
    void addHitable(hitable* a);
    
    virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const override;
};

#endif /* hitableList_hpp */

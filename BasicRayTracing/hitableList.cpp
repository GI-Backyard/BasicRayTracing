//
//  hitableList.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "hitableList.hpp"

HitableList::~HitableList() {
    for(const auto& i : hitables) {
        delete i;
    }
}

void HitableList::addHitable(Hitable* a) {
    hitables.push_back(a);
}

bool HitableList::hit(const Ray& r, float tMin, float tMax, HitRecord& rec) const {
    bool hited = false;
    HitRecord tmp;
    float currentTMax = tMax;
    for(const auto& ele : hitables) {
        if(ele->hit(r, tMin, currentTMax, tmp)) {
            hited = true;
            rec = tmp;
            currentTMax = tmp.t;
        }
    }
    
    return hited;
}

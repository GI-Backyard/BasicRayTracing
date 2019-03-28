//
//  hitableList.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "hitableList.hpp"

hitableList::~hitableList() {
    for(const auto& i : hitables) {
        delete i;
    }
}

void hitableList::addHitable(hitable* a) {
    hitables.push_back(a);
}

bool hitableList::hit(const ray& r, float tMin, float tMax, hitRecord& rec) const {
    bool hited = false;
    hitRecord tmp;
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

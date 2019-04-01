//
//  perlin.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/4/1.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef perlin_hpp
#define perlin_hpp
#include "vec3.hpp"
#include <vector>
class Perlin {
private:
    static std::vector<float> ranFloat;
    static std::vector<int> permX;
    static std::vector<int> permY;
    static std::vector<int> permZ;
    
public:
    static std::vector<float> perlinGen();
    static std::vector<int> perlinGenPerm();
    float noise(const Vec3& p) const;
};

#endif /* perlin_hpp */

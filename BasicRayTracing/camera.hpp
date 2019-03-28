//
//  camera.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include "ray.hpp"

class camera {
private:
    vec3 origin;
    vec3 lowLeftCorner;
    vec3 horizontal;
    vec3 vertical;
public:
    
    camera() {
        lowLeftCorner = vec3( -2, -1, -1);
        horizontal = vec3(4, 0, 0);
        vertical = vec3(0, 2, 0);
        origin = vec3(0, 0, 0);
    }
    
    ray getRay(float u, float v) {
        return ray(origin, lowLeftCorner + u * horizontal + v * vertical - origin);
    }
};

#endif /* camera_hpp */

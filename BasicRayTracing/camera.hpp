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
#include <math.h>

class camera {
private:
    vec3 origin;
    vec3 lowLeftCorner;
    vec3 horizontal;
    vec3 vertical;
public:
    
    camera(const vec3& eye, const vec3& focus, const vec3& up,float fov, float aspect) {
        vec3 u, v, w;
        w = getUnitVector(eye - focus);
        u = getUnitVector(cross(up, w));
        v = cross(w, u);
        origin = eye;
        float fovInRad = fov * M_PI / 180;
        float halfHeight = tan(fovInRad / 2);
        float halfWidth = halfHeight * aspect;
        
        lowLeftCorner = origin - halfWidth * u - halfHeight * v - w;
        horizontal = 2 * halfWidth * u;
        vertical = 2 * halfHeight * v;
        
    }
    
    ray getRay(float u, float v) {
        return ray(origin, lowLeftCorner + u * horizontal + v * vertical - origin);
    }
};

#endif /* camera_hpp */

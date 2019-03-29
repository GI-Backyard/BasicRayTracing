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

inline vec3 randomInUnitDisk() {
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    } while(dot(p, p) >= 1);
    return p;
}

class camera {
private:
    vec3 origin;
    vec3 lowLeftCorner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u;
    vec3 v;
    vec3 w;
    float lenghRadius;
public:
    
    camera(const vec3& eye, const vec3& focus, const vec3& up,float fov, float aspect, float aperture = 0, float focusDist = 1) {
        lenghRadius = aperture / 2;
        w = getUnitVector(eye - focus);
        u = getUnitVector(cross(up, w));
        v = cross(w, u);
        origin = eye;
        float fovInRad = fov * M_PI / 180;
        float halfHeight = tan(fovInRad / 2);
        float halfWidth = halfHeight * aspect;
        
        lowLeftCorner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
        horizontal = 2 * focusDist * halfWidth * u;
        vertical = 2 * focusDist * halfHeight * v;
        
    }
    
    ray getRay(float s, float t) {
        vec3 rd = lenghRadius * randomInUnitDisk();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(origin + offset, lowLeftCorner + s * horizontal + t * vertical - origin - offset);
    }
};

#endif /* camera_hpp */

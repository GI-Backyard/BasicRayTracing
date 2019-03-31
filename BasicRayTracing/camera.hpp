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

inline Vec3 randomInUnitDisk() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(drand48(), drand48(), 0) - Vec3(1, 1, 0);
    } while(dot(p, p) >= 1);
    return p;
}

class Camera {
private:
    Vec3 origin;
    Vec3 lowLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u;
    Vec3 v;
    Vec3 w;
    float lenghRadius;
    float time0;
    float time1;
public:
    
    Camera(const Vec3& eye, const Vec3& focus, const Vec3& up,float fov, float aspect, float aperture,
           float focusDist, float t0, float t1) {
        time0 = t0;
        time1 = t1;
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
    
    Ray getRay(float s, float t) {
        Vec3 rd = lenghRadius * randomInUnitDisk();
        Vec3 offset = u * rd.x() + v * rd.y();
        float time  = time0 + drand48() * (time1 - time0);
        return Ray(origin + offset, lowLeftCorner + s * horizontal + t * vertical - origin - offset, time);
    }
};

#endif /* camera_hpp */

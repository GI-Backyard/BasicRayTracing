//
//  texture.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/4/1.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "texture.hpp"

ConstantTexture::ConstantTexture(const Vec3& c)
: color(c){
    
}

Vec3 ConstantTexture::value(float u, float v, const Vec3& p) const {
    return color;
}

CheckerTexture::CheckerTexture(Texture* t0, Texture* t1)
: odd(t0), even(t1){
    
}

CheckerTexture::~CheckerTexture() {
    delete odd;
    delete even;
}

Vec3 CheckerTexture::value(float u, float v, const Vec3& p) const {
    float sines = sin(p.x() * 10) * sin(p.y() * 10) * sin(p.z() * 10);
    if(sines > 0) return even->value(u, v, p);
    else return odd->value(u, v, p);
}

NoiseTexture::NoiseTexture(float s) {
    scale = s;
}
Vec3 NoiseTexture::value(float u, float v, const Vec3& p) const {
//    return Vec3(1, 1, 1) * noise.turb(scale * p);
    return Vec3(1, 1, 1) * 0.5 * (1 + sin(scale * p.z() + 10 * noise.turb(p)));
}

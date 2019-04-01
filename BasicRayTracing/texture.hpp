//
//  texture.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/4/1.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef texture_h
#define texture_h
#include "vec3.hpp"

class Texture {
public:
    virtual ~Texture() {}
    virtual Vec3 value(float u, float v, const Vec3& p) const = 0;
};

class ConstantTexture : public Texture {
private:
    Vec3 color;
public:
    ConstantTexture(const Vec3& c);
    virtual Vec3 value(float u, float v, const Vec3& p) const override;
};

class CheckerTexture : public Texture {
private:
    Texture* odd;
    Texture* even;
public:
    CheckerTexture(Texture* t0, Texture* t1);
    ~CheckerTexture();
    virtual Vec3 value(float u, float v, const Vec3& p) const override;
};
#endif /* texture_h */

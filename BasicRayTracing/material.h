//
//  material.h
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/28.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef material_h
#define material_h
#include "ray.hpp"
#include "hitable.h"
#include "texture.hpp"

class Material {
public:
    virtual ~Material() {}
    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const = 0;
    virtual Vec3 emitted(float u, float v, const Vec3& p) const {
        return Vec3(0, 0, 0);
    }
    
    static inline Vec3 randomInUnitSphere();
    static inline Vec3 reflect(const Vec3& in, const Vec3& normal);
    static inline bool refract(const Vec3& vIn, const Vec3& n, float niOverNt, Vec3& refracted);
    static inline float schlick(float cosine, float refIdx);
};

class Lambert : public Material {
private:
    const Texture* texture;
public:
    ~Lambert();
    Lambert(const Texture* tex);
    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const override;
};

class Dielectric : public Material {
private:
    float refactIndex;
public:
    Dielectric(float ri) { refactIndex = ri; }
    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const override;
};

class Metal : public Material {
private:
    Vec3 albedo;
    float fuzzy;
public:
    Metal(const Vec3& color, float f = 0) {
        albedo = color;
        if(f > 1) fuzzy = 1;
        else if(f < 0) fuzzy = 0;
        else fuzzy = f;
    }
    
    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const override;
};

class DiffuseLight : public Material {
public:
    Texture* emit;
public:
    DiffuseLight(Texture* tex) {
        emit = tex;
    }
    
    ~DiffuseLight() {
        delete emit;
    }
    
    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Vec3& atten, Ray& scatted) const { return false; }
    virtual Vec3 emitted(float u, float v, const Vec3& p) const {
        return emit->value(u, v, p);
    }
    
};

#endif /* material_h */

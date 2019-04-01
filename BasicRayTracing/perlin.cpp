//
//  perlin.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/4/1.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "perlin.hpp"

std::vector<Vec3> Perlin::ranVec3 = Perlin::perlinGen();
std::vector<int> Perlin::permX = Perlin::perlinGenPerm();
std::vector<int> Perlin::permY = Perlin::perlinGenPerm();
std::vector<int> Perlin::permZ = Perlin::perlinGenPerm();
inline float perlinInterp(Vec3 c[2][2][2], float u, float v, float w) {
    float uu = u * u * (3-2*u);
    float vv = v * v * (3-2*v);
    float ww = w * w * (3-2*w);
    float accum = 0;
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
            for(int k = 0; k < 2; ++k) {
                float pp = dot(c[i][j][k], Vec3(u - i, v - j, w - k));
                accum += (i*uu + (1-i)*(1-uu)) * (j*vv+(1-j)*(1-vv)) * (k*ww+(1-k)*(1-ww)) * pp;
            }
    return accum;
}

std::vector<Vec3> Perlin::perlinGen() {
    std::vector<Vec3> result(256);
    for(int i = 0; i < 256; ++i) {
        result[i] = getUnitVector(Vec3(1 - 2 * drand48(), 1 - 2 * drand48(), 1 - 2 * drand48()));
    }
    return result;
}

void permute(int* p, int n) {
    for(int i = n - 1; i > 0; i--) {
        int target = int(drand48() * (i + 1));
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

std::vector<int> Perlin::perlinGenPerm() {
    std::vector<int> result(256);
    for(int i = 0; i < 256; i++) {
        result[i] = i;
    }
    permute(&result[0], 256);
    return result;
}

float Perlin::noise(const Vec3& p) const {
    float u = p.x() - floor(p.x());
    float v = p.y() - floor(p.y());
    float w = p.z() - floor(p.z());
    int i = floor(p.x());
    int j = floor(p.y());
    int k = floor(p.z());
    Vec3 c[2][2][2];
    for(int di = 0; di < 2; ++di)
        for(int dj = 0; dj < 2; ++dj)
            for(int dk = 0; dk < 2; ++dk)
                c[di][dj][dk] = ranVec3[permX[(i + di) & 255] ^ permY[(j + dj) & 255] ^ permZ[(k + dk) & 255]];
    return perlinInterp(c, u, v, w);
    //return ranFloat[permX[i]^permY[j]^permZ[k]];
}

float Perlin::turb(const Vec3& p, float depth) const {
    float accum = 0;
    Vec3 tmpP = p;
    float weight = 1;
    for(int i = 0; i < depth; ++i) {
        accum += weight * noise(tmpP);
        tmpP *= 2;
        weight *= 0.5;
    }
    
    return fabs(accum);
}

//
//  perlin.cpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/4/1.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#include "perlin.hpp"

std::vector<float> Perlin::ranFloat = Perlin::perlinGen();
std::vector<int> Perlin::permX = Perlin::perlinGenPerm();
std::vector<int> Perlin::permY = Perlin::perlinGenPerm();
std::vector<int> Perlin::permZ = Perlin::perlinGenPerm();
inline float trilinearInterP(float c[2][2][2], float u, float v, float w) {
    float accum = 0;
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
            for(int k = 0; k < 2; ++k)
                accum += (i*u + (1-i)*(1-u)) * (j*v+(1-j)*(1-v)) * (k*w+(1-k)*(1-w)) * c[i][j][k];
    return accum;
}

std::vector<float> Perlin::perlinGen() {
    std::vector<float> result(256);
    for(int i = 0; i < 256; ++i) {
        result[i] = drand48();
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
//    float u = p.x() - floor(p.x());
//    float v = p.y() - floor(p.y());
//    float w = p.z() - floor(p.z());
    int i = int(4 * p.x()) & 255;
    int j = int(4 * p.y()) & 255;
    int k = int(4 * p.z()) & 255;
//    for(int di = 0; di < 2; ++di)
//        for(int dj = 0; dj < 2; ++dj)
//            for(int dk = 0; dk < 2; ++dk)
//                i;
    return ranFloat[permX[i] ^ permY[j] ^ permZ[k]];
}

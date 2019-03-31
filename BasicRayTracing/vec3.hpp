//
//  vec3.hpp
//  BasicRayTracing
//
//  Created by huabingxu on 2019/3/27.
//  Copyright © 2019 harrisonxu. All rights reserved.
//

#ifndef vec3_hpp
#define vec3_hpp

#include <math.h>
#include <iostream>

class Vec3 {
public:
    float e[3];
public:
    Vec3() { e[0] = e[1] = e[2] = 0; }
    Vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
    Vec3(const Vec3& v) { e[0] = v.e[0]; e[1] = v.e[1]; e[2] = v.e[2]; }
    
    inline float x() const { return e[0];}
    inline float y() const { return e[1];}
    inline float z() const { return e[2];}
    inline float r() const { return e[0];}
    inline float g() const { return e[1];}
    inline float b() const { return e[2];}
    
    inline const Vec3& operator=(const Vec3& v) {e[0] = v.e[0]; e[1] = v.e[1]; e[2] = v.e[2]; return *this; }
    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }
    
    inline Vec3& operator +=(const Vec3& v);
    inline Vec3& operator -=(const Vec3& v);
    inline Vec3& operator *=(const Vec3& v);
    inline Vec3& operator /=(const Vec3& v);
    inline Vec3& operator *=(float t);
    inline Vec3& operator /=(float t);
    
    inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    inline float squareLength() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    
};

inline std::istream& operator>>(std::istream& is, Vec3& v) {
    is >> v.e[0] >> v.e[1] >> v.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, Vec3& v) {
    os << v.e[0] << " " << v.e[1] << " "<< v.e[2];
    return os;
}

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vec3 operator*(float t, const Vec3& v) {
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator*(const Vec3& v, float t) {
    return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vec3 operator/(const Vec3& v, float t) {
    return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline float dot(const Vec3& v1, const Vec3& v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline Vec3& Vec3::operator +=(const Vec3& v) {
    e[0] += v.e[0]; e[1] += v.e[1]; e[2] += v.e[2];
    return *this;
}

inline Vec3& Vec3::operator -=(const Vec3& v) {
    e[0] -= v.e[0]; e[1] -= v.e[1]; e[2] -= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator *=(const Vec3& v) {
    e[0] *= v.e[0]; e[1] *= v.e[1]; e[2] *= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator /=(const Vec3& v) {
    e[0] /= v.e[0]; e[1] /= v.e[1]; e[2] /= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator *=(float t) {
    e[0] *= t; e[1] *= t; e[2] *= t;
    return *this;
}

inline Vec3& Vec3::operator /=(float t) {
    e[0] /= t; e[1] /= t; e[2] /= t;
    return *this;
}

inline Vec3 getUnitVector(const Vec3& v) {
    return v / v.length();
}

#endif /* vec3_hpp */

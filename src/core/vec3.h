//
//  vec3.h
//  RayTracing
//
//  Created by 木内舜司 on 2020/04/11.
//  Copyright © 2020 木内舜司. All rights reserved.
//

#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

#include "Util.h"

template <typename T>
class type3 {
public:
    type3() : x(0), y(0), z(0) {}
    type3(T e0, T e1, T e2) : x(e0), y(e1), z(e2) {}
    type3(T c) : x(c), y(c), z(c) {}
    
    type3 operator-() const { return type3(-x, -y, -z); }
    T operator[](int i) const { 
        if(i == 0) return x;
        else if(i == 1) return y;
        else if(i == 2) return z;
    }
    T& operator[](int i) {
        if(i == 0) return x;
        else if(i == 1) return y;
        else if(i == 2) return z;
    }
    
    type3& operator+=(const type3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    
    type3& operator*=(const T t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    
    type3 &operator/=(const T t) {
        return *this *= 1/t;
    }
    
    T length() const {
        return sqrt(length_squared());
    }
    
    T length_squared() const {
        return x*x + y*y + z*z;
    }

    inline static type3 random() {
        return type3(random_double(), random_double(), random_double());
    }

    inline static type3 random(T min, T max) {
        return type3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
    
    /*void write_color(std::ostream &out, int samples_per_pixel) {
        // Devide the color total by the number of samples.
        // for a gamma value of 2.0
        auto scale = 1.0 / samples_per_pixel;
        auto r = sqrt(scale * x);
        auto g = sqrt(scale * y);
        auto b = sqrt(scale * z);

        // Write the translated [0, 255] value of each color component.
        out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
    }*/
    
public:
    T x, y, z;
};

// vec3 utility functions
inline std::ostream& operator<<(std::ostream &out, const type3 &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline type3 operator+(const type3 &u, const type3 &v) {
    return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline type3 operator-(const type3 &u, const type3 &v) {
    return type3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline type3 operator*(const type3 &u, const type3 &v) {
    return type3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline type3 operator*(double t, const type3 &v) {
    return type3(t*v.x, t*v.y, t*v.z);
}

inline type3 operator*(const type3 &v, double t) {
    return t * v;
}

inline type3 operator/(type3 v, double t) {
    return (1/t) * v;
}

inline double dot(const type3 &u, const type3 &v) {
    return u.x * v.x
    + u.y * v.y
    + u.z * v.z;
}

inline type3 cross(const type3 &u, const type3 &v) {
    return type3(u.y * v.z - u.z * v.y,
                u.z * v.x - u.x * v.z,
                u.x * v.y - u.y * v.x);
}

typedef type3<double> vec3;
typedef type3<unsigned int> uint3;
typedef type3<int> int3;
typedef type3<unsigned char> rgb;

// TODO: Implement of zero-division check. If v = vec3(0.0), zero-division will occur.
inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

vec3 random_unit_vector() {
    auto a = random_double(0, 2*pi);
    auto z = random_double(-1,1);
    auto r = sqrt(1 - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}

vec3 random_in_unit_sphere() {
    while(true) {
        auto p = vec3::random(-1,1);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else 
        return -in_unit_sphere;
}

vec3 random_in_unit_disk() {
    while(true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if(p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n) * n;
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perp;
}

#endif /* vec3_h */

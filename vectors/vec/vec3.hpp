

#pragma once

#include <cmath>
#include <iostream>

namespace vec {

    using std::sqrt;

    class vec3 {
        public:
            vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

            double x() const { return e[0]; }
            double y() const { return e[1]; }
            double z() const { return e[2]; }

            vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

            __attribute__((always_inline)) vec3& operator+=(const vec3 &v) {
                e[0] += v.e[0];
                e[1] += v.e[1];
                e[2] += v.e[2];
                return *this;
            }

            __attribute__((always_inline)) vec3& operator*=(const vec3 &v) {
                e[0] *= v.e[0];
                e[1] *= v.e[1];
                e[2] *= v.e[2];
                return *this;
            }

            __attribute__((always_inline)) vec3& operator*=(const double t) {
                e[0] *= t;
                e[1] *= t;
                e[2] *= t;
                return *this;
            }

            __attribute__((always_inline))
                vec3& operator/=(const double t) {
                    return *this *= 1/t;
                }

            __attribute__((always_inline)) double length() const {
                return sqrt(length_squared());
            }

            __attribute__((always_inline))
                double length_squared() const {
                    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
                }

        public:
            double e[3];
    };

    __attribute__((always_inline))
        inline vec3 operator+(const vec3 &u, const vec3 &v) {
            return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
        }

    __attribute__((always_inline))
        inline vec3 operator-(const vec3 &u, const vec3 &v) {
            return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
        }

    __attribute__((always_inline))
        inline vec3 operator*(const vec3 &u, const vec3 &v) {
            return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
        }

    __attribute__((always_inline))
        inline vec3 operator*(double t, const vec3 &v) {
            return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
        }

    __attribute__((always_inline))
        inline vec3 operator*(const vec3 &v, double t) {
            return t * v;
        }

    __attribute__((always_inline))
        inline vec3 operator/(vec3 v, double t) {
            return (1/t) * v;
        }

    //__attribute__((always_inline))
    __attribute__((noinline))
        double dot(const vec3 &u, const vec3 &v) {
            return u.e[0] * v.e[0]
                + u.e[1] * v.e[1]
                + u.e[2] * v.e[2];
        }

    inline vec3 cross(const vec3 &u, const vec3 &v) {
        return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    __attribute__((always_inline))
        inline vec3 unit_vector(vec3 v) {
            return v / v.length();
        }
}

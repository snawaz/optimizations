

#pragma once

#include <cmath>
#include <iostream>

namespace vec {
    using std::sqrt;

    class alignas(16) vec4 {
        public:
            vec4(double e0, double e1, double e2, double e3) : e{e0, e1, e2, e3} {}

            double x() const { return e[0]; }
            double y() const { return e[1]; }
            double z() const { return e[2]; }
            double a() const { return e[3]; }

            vec4 operator-() const { return vec4(-e[0], -e[1], -e[2], -e[3]); }

            __attribute__((always_inline)) vec4& operator+=(const vec4 &v) {
                e[0] += v.e[0];
                e[1] += v.e[1];
                e[2] += v.e[2];
                e[3] += v.e[3];
                return *this;
            }

            //__attribute__((always_inline))
            __attribute__((noinline))
            vec4& operator*=(const vec4 &v) {
                #if 0
                e[0] *= v.e[0];
                e[1] *= v.e[1];
                e[2] *= v.e[2];
                e[3] *= v.e[3];
                #else
                auto ymm1 = _mm256_loadu_pd(e);
                auto ymm2 = _mm256_loadu_pd(v.e);
                auto ymm = _mm256_mul_pd(ymm1, ymm2);
                _mm256_storeu_pd(e, ymm);
                #endif
                return *this;
            }

            __attribute__((always_inline)) vec4& operator*=(const double t) {
                e[0] *= t;
                e[1] *= t;
                e[2] *= t;
                e[3] *= t;
                return *this;
            }

            __attribute__((always_inline))
                vec4& operator/=(const double t) {
                    return *this *= 1/t;
                }

            __attribute__((always_inline)) double length() const {
                return sqrt(length_squared());
            }

            __attribute__((always_inline))
                double length_squared() const {
                    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2] + e[3] * e[3];
                }

        public:
            double e[4];
    };

    __attribute__((always_inline))
        inline vec4 operator+(const vec4 &u, const vec4 &v) {
            return vec4(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
        }

    __attribute__((always_inline))
        inline vec4 operator-(const vec4 &u, const vec4 &v) {
            return vec4(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3] - v.e[3]);
        }

    //__attribute__((always_inline))
    __attribute__((noinline))
        inline vec4 operator*(const vec4 &u, const vec4 &v) {
            return vec4(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2], u.e[3] * v.e[3]);
        }

    __attribute__((always_inline))
        inline vec4 operator*(double t, const vec4 &v) {
            return vec4(t*v.e[0], t*v.e[1], t*v.e[2], t*v.e[3]);
        }

    __attribute__((always_inline))
        inline vec4 operator*(const vec4 &v, double t) {
            return t * v;
        }

    __attribute__((always_inline))
        inline vec4 operator/(vec4 v, double t) {
            return (1/t) * v;
        }

    //__attribute__((always_inline))
    __attribute__((noinline))
        double dot(const vec4 &u, const vec4 &v) {
            return u.e[0] * v.e[0]
                + u.e[1] * v.e[1]
                + u.e[2] * v.e[2]
                + u.e[3] * v.e[3];
        }

    inline vec4 cross(const vec4 &u, const vec4 &v) {
        return vec4(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[3] - u.e[3] * v.e[2],
                u.e[3] * v.e[0] - u.e[0] * v.e[3],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    __attribute__((always_inline))
        inline vec4 unit_vector(vec4 v) {
            return v / v.length();
        }

}

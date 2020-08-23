
#include <vector>
#include <iostream>
#include <cstdlib>
#include <chrono>

// #define VEC3

#include "externals/version2/vectorclass.h"
#ifdef VEC3
    #include "vec/vec3.hpp"
#else
    #include "vec/vec4.hpp"
#endif
#include "random10000.hpp"
#include "utils.hpp"

void benchmark_3d_vec();
void benchmark_4d_vec();

int main() {
#ifdef VEC3
    benchmark_3d_vec();
#else
    benchmark_4d_vec();
#endif
}

__attribute__((noinline))
auto DotVec4d(Vec4d const &a, Vec4d const & b) {
    return horizontal_add(a * b);
}

#ifdef VEC3
__attribute__((noinline))
void benchmark_3d_vec() {
    constexpr auto size = 81000000;
    using Vec3d = Vec4d; //ignore the 4th dimension and use cutoff

    std::vector<vec::vec3> my_vecs;
    std::vector<Vec3d> their_vecs;
    measure("vectors populated", [&] {
       my_vecs.reserve(size);
       their_vecs.reserve(size);
       for(auto i = 0; i < size; i++) {
            auto x = random_double();
            auto y = random_double();
            auto z = random_double();
            my_vecs.emplace_back(x, y, z);
            their_vecs.emplace_back(x, y, z, 0);
        }
    });
    vec::vec3 my_product(1, 1, 1);
    Vec3d their_product(1, 1, 1, 0);
    measure("my product", [&] {
        for(auto e : my_vecs) {
            my_product *= e;
        }
    });
    measure("their product", [&] {
        for(auto e : their_vecs) {
            their_product *= e;//.cutoff(3);
        }
    });
    std::cout << my_product << std::endl;
    std::cout << their_product << std::endl;

    double my_dot = 0;
    double their_dot = 0;
    measure("my dot", [&] {
        for(auto e : my_vecs) {
            my_dot += dot(e, e);
        }
    });
    measure("their dot", [&] {
        for(auto e : their_vecs) {
            //their_dot += horizontal_add((e*e).cutoff(3));
            //auto e3 = e.cutoff(3);
            //their_dot += horizontal_add(e3 * e3);
            //their_dot += horizontal_add(e*e);
            their_dot += DotVec4d(e, e);
        }
    });
    std::cout << my_dot << std::endl;
    std::cout << their_dot << std::endl;
}
#else
__attribute__((noinline))
void mult_assign(Vec4d & a, Vec4d const & b) {
    a *= b;
}

__attribute__((noinline))
void benchmark_4d_vec() {
    constexpr auto size = 81000000;
    std::vector<vec::vec4> my_vecs;
    std::vector<Vec4d> their_vecs;
    measure("vectors populated", [&] {
       my_vecs.reserve(size);
       their_vecs.reserve(size);
       for(auto i = 0; i < size; i++) {
            auto x = random_double();
            auto y = random_double();
            auto z = random_double();
            auto a = random_double();
            my_vecs.emplace_back(x, y, z, a);
            their_vecs.emplace_back(x, y, z, a);
        }
    });
    vec::vec4 my_product(1, 1, 1, 1);
    Vec4d their_product(1, 1, 1, 1);
    measure("my product", [&] {
        for(auto const & e : my_vecs) {
            my_product *= e;
        }
    });
    measure("their product", [&] {
        for(auto const & e : their_vecs) {
            mult_assign(their_product, e);
        }
    });
    std::cout << my_product << std::endl;
    std::cout << their_product << std::endl;

    double my_dot = 0;
    double their_dot = 0;
    measure("my dot", [&] {
        for(auto const & e : my_vecs) {
            my_dot += dot(e, e);
        }
    });
    measure("their dot", [&] {
        for(auto const & e : their_vecs) {
            their_dot += horizontal_add(e*e);
        }
    });
    std::cout << my_dot << std::endl;
    std::cout << their_dot << std::endl;
}
#endif

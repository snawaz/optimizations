
#include <vector>
#include <iostream>
#include <cstdlib>
#include <chrono>

#include "vec/vec4.hpp"
#include "vectorclass/version2/vectorclass.h"
#include "random10000.hpp"

#define USE_STD_RAND

#ifdef USE_STD_RAND
auto random_double()  {
    return 0.5 + rand() / (RAND_MAX + 1.0);
}
#else
auto random_double()  {
    random_index = (random_index + 1) % (sizeof(random_numbers) / sizeof (random_numbers[0]));
    return random_numbers[random_index]; 
}
#endif

template<typename F>
void measure(char const *  const message, F && f) {
    auto start = std::chrono::steady_clock::now();
    f();
    auto end = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << message << ": " << ms << " ms" << std::endl;
}

std::ostream & operator << (std::ostream & out, vec::vec4 const & v) {
    return out << "vec4{ " << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.a() << "}";
}

std::ostream & operator << (std::ostream & out, Vec4d const & v) {
    return out << "Vec4d{ " << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << "}";
}

int main() {
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
            their_product *= e; 
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


#pragma once

#ifdef VEC3
std::ostream & operator << (std::ostream & out, vec::vec3 const & v) {
    return out << "vec4{ " << v.x() << ", " << v.y() << ", " << v.z() << "}";
}
#else
std::ostream & operator << (std::ostream & out, vec::vec4 const & v) {
    return out << "vec4{ " << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.a() << "}";
}
#endif

std::ostream & operator << (std::ostream & out, Vec4d const & v) {
    return out << "Vec4d{ " << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << "}";
}

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


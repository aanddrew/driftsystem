#include "vec3.h"

#include <math.h>

struct Vec3 {
    float x;
    float y;
    float z;
};

float Vec3_dot(Vec3 a, Vec3 b) {
    return (a.x * b.x)
        +  (a.y * b.y)
        +  (a.z * b.z);
}
float Vec3_length(Vec3 a) {
    return sqrt(Vec3_dot(a, a));
}

Vec3 Vec3_add(Vec3 a, Vec3 b) { return (Vec3) { a.x + b.x, a.y + b.y, a.z + b.z }; }
Vec3 Vec3_sub(Vec3 a, Vec3 b) { return (Vec3) { a.x - b.x, a.y - b.y, a.z - b.z }; }
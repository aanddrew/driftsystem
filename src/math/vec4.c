#include "vec4.h"

#include <math.h>

float Vec4_dot(Vec4 a, Vec4 b) {
    return (a.x * b.x)
        +  (a.y * b.y)
        +  (a.z * b.z)
        +  (a.w * b.w);
}
float Vec4_length(Vec4 a) {
    return sqrt(Vec4_dot(a, a));
}

Vec4 Vec4_add(Vec4 a, Vec4 b) { return (Vec4) { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w }; }
Vec4 Vec4_sub(Vec4 a, Vec4 b) { return (Vec4) { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w }; }
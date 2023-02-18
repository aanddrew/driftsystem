#include "vec2.h"

#include <math.h>

struct Vec2 {
    float x;
    float y;
};

float Vec2_dot(Vec2 a, Vec2 b) {
    return (a.x * b.x)
        +  (a.y * b.y);
}
float Vec2_length(Vec2 a) {
    return sqrt(Vec2_dot(a, a));
}

Vec2 Vec2_add(Vec2 a, Vec2 b) { return (Vec2) { a.x + b.x, a.y + b.y }; }
Vec2 Vec2_sub(Vec2 a, Vec2 b) { return (Vec2) { a.x - b.x, a.y - b.y }; }
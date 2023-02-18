#ifndef VEC2_H
#define VEC2_H

struct Vec2;
typedef struct Vec2 Vec2;

float Vec2_dot(Vec2 a, Vec2 b);
float Vec2_length(Vec2 a);

Vec2 Vec2_add(Vec2 a, Vec2 b);
Vec2 Vec2_sub(Vec2 a, Vec2 b);

#endif
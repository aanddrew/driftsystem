#ifndef VEC4_H
#define VEC4_H

struct Vec4;
typedef struct Vec4 Vec4;

float Vec4_dot(Vec4 a, Vec4 b);
float Vec4_length(Vec4 a);

Vec4 Vec4_add(Vec4 a, Vec4 b);
Vec4 Vec4_sub(Vec4 a, Vec4 b);

#endif
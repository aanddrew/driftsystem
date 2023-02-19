#ifndef VEC4_H
#define VEC4_H

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

float Vec4_dot(Vec4 a, Vec4 b);
float Vec4_length(Vec4 a);

Vec4 Vec4_add(Vec4 a, Vec4 b);
Vec4 Vec4_sub(Vec4 a, Vec4 b);

#endif
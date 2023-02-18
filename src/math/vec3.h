#ifndef VEC3_H
#define VEC3_H

struct Vec3;
typedef struct Vec3 Vec3;

float Vec3_dot(Vec3 a, Vec3 b);
float Vec3_length(Vec3 a);

Vec3 Vec3_add(Vec3 a, Vec3 b);
Vec3 Vec3_sub(Vec3 a, Vec3 b);

#endif
#ifndef MAT2_H
#define MAT2_H

#include "vec2.h"
#include <stdint.h>

typedef struct Mat2 {
    Vec2 x;
    Vec2 y;
} Mat2;


Vec2 Mat2_col(Mat2 m, uint32_t index);
Vec2 Mat2_row(Mat2 m, uint32_t index);

Mat2 Mat2_zero();

Mat2 Mat2_mul(Mat2 left, Mat2 right);
Mat2 Mat2_mul_vec(Mat2 left, Vec2 right);
Mat2 Mat2_transpose(Mat2 m);

#endif
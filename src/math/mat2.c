#include "mat2.h"

Mat2 Mat2_zero() {
    return (Mat2) {
        Vec2_zero(),
        Vec2_zero()
    };
}

Vec2 Mat2_col(Mat2 m, uint32_t index) {
    switch (index) {
        case 0: return m.x; break;
        case 1: return m.y; break;
        default: {
            return Vec2_zero(); 
        } break;
    }
}
Vec2 Mat2_row(Mat2 m, uint32_t index) {
    switch (index) {
        case 0: return (Vec2) { .x= m.x.x, .y= m.y.x }; break;
        case 1: return (Vec2) { .x= m.x.y, .y= m.y.y }; break;
        default: {
            return Vec2_zero();
        } break;
    }
}

Mat2 Mat2_mul(Mat2 left, Mat2 right);
Mat2 Mat2_mul_vec(Mat2 left, Vec2 right);
Mat2 Mat2_transpose(Mat2 m);

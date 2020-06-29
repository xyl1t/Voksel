//
//  tensorMath.cpp
//  Voksel
//
//  Created by Marat Isaw on 21.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#include "tensorMath.hpp"
#include <iostream>

// TODO: implement transpose() and determinant() for matrix classes 

/* tem::vec2 ==================================================== */

tem::vec2& tem::vec2::operator=(const tem::vec2& other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}
tem::vec2& tem::vec2::operator+=(const tem::vec2& other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
}
tem::vec2& tem::vec2::operator-=(const tem::vec2& other) {
    this->x -= other.x;
    this->y -= other.y;
    return *this;
}
tem::vec2& tem::vec2::operator*=(const float other) {
    this->x *= other;
    this->y *= other;
    return *this;
}
tem::vec2& tem::vec2::operator/=(const float other) {
    this->x /= other;
    this->y /= other;
    return *this;
}
tem::vec2 tem::vec2::operator+(const tem::vec2& other) {
    return tem::vec2 { this->x + other.x, this->y + other.y };
}
tem::vec2 tem::vec2::operator-(const tem::vec2& other) {
    return tem::vec2 { this->x - other.x, this->y - other.y };
}
tem::vec2 tem::vec2::operator*(const float other) {
    return tem::vec2 { this->x * other, this->y * other };
}
float tem::vec2::operator*(const tem::vec2& other) {
    return this->x * other.x + this->y * other.y;
}
tem::vec2 tem::vec2::operator/(const float other) {
    return tem::vec2 { this->x / other, this->y / other };
}


/* tem::vec3 =================================================================== */

tem::vec3& tem::vec3::operator=(const tem::vec3& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}
tem::vec3& tem::vec3::operator+=(const tem::vec3& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}
tem::vec3& tem::vec3::operator-=(const tem::vec3& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}
tem::vec3& tem::vec3::operator*=(const float other) {
    this->x *= other;
    this->y *= other;
    this->z *= other;
    return *this;
}
tem::vec3& tem::vec3::operator/=(const float other) {
    this->x /= other;
    this->y /= other;
    this->z /= other;
    return *this;
}
tem::vec3 tem::vec3::operator+(const tem::vec3& other) {
    return tem::vec3 { this->x + other.x, this->y + other.y, this->z + other.z };
}
tem::vec3 tem::vec3::operator-(const tem::vec3& other) {
    return tem::vec3 { this->x - other.x, this->y - other.y, this->z - other.z };
}
tem::vec3 tem::vec3::operator*(const float other) {
    return tem::vec3 { this->x * other, this->y * other, this->z * other };
}
float tem::vec3::operator*(const tem::vec3& other) {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}
tem::vec3 tem::vec3::operator/(const float other) {
    return tem::vec3 { this->x / other, this->y / other, this->z / other };
}


/* tem::vec4 =================================================================== */

tem::vec4& tem::vec4::operator=(const tem::vec4& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->w = other.w;
    return *this;
}
tem::vec4& tem::vec4::operator+=(const tem::vec4& other) {
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
    return *this;
}
tem::vec4& tem::vec4::operator-=(const tem::vec4& other) {
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;
    return *this;
}
tem::vec4& tem::vec4::operator*=(const float other) {
    this->x *= other;
    this->y *= other;
    this->z *= other;
    this->w *= other;
    return *this;
}
tem::vec4& tem::vec4::operator/=(const float other) {
    this->x /= other;
    this->y /= other;
    this->z /= other;
    this->w /= other;
    return *this;
}
tem::vec4 tem::vec4::operator+(const tem::vec4& other) {
    return tem::vec4 { this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w };
}
tem::vec4 tem::vec4::operator-(const tem::vec4& other) {
    return tem::vec4 { this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w };
}
tem::vec4 tem::vec4::operator*(const float other) {
    return tem::vec4 { this->x * other, this->y * other, this->z * other, this->w * other };
}
float tem::vec4::operator*(const tem::vec4& other) {
    return this->x * other.x + this->y * other.y + this->z * other.z + this->w * other.w;
}
tem::vec4 tem::vec4::operator/(const float other) {
    return tem::vec4 { this->x / other, this->y / other, this->z / other, this->w / other };
}



/* tem::mat2x2 =================================================================== */

tem::mat2x2::mat2x2() : mat{ } {
}
tem::mat2x2::mat2x2(const float initValue) : mat{ }{
    for(int i = 0; i < 2; i++)
        this->mat[i+2*i] = initValue;
}
tem::mat2x2::mat2x2(const float mat[4]) {
    for(int i = 0; i < 4; i++)
        this->mat[i] = mat[i];
}
tem::mat2x2::mat2x2(const tem::mat2x2& other) {
    for(int i = 0; i < 4; i++)
        this->mat[i] = other.mat[i];
}
tem::mat2x2 tem::mat2x2::transpose() {
    mat2x2 mat;
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            mat[i + j * 2] = this->mat[j + i * 2];
        }
    }
    
    return mat;
}
tem::mat2x2 tem::mat2x2::inverse() {
    mat2x2 mat = mat2x2::Null();
    
    float det = this->determinant();
    if(det == 0) return mat;
    
    float invdet = 1.f / det;
    
    mat[0] =  this->mat[3] * invdet;
    mat[1] = -this->mat[1] * invdet;
    mat[2] = -this->mat[2] * invdet;
    mat[3] =  this->mat[0] * invdet;
    
    return mat;
}
float& tem::mat2x2::operator[](int index) {
    return this->mat[index];
}
tem::mat2x2& tem::mat2x2::operator=(const tem::mat2x2& other) {
    for(int i = 0; i < 4; i++)
        this->mat[i] = other.mat[i];
    return *this;
}
tem::mat2x2& tem::mat2x2::operator+=(const tem::mat2x2& other) {
    for(int i = 0; i < 4; i++) {
        this->mat[i] += other.mat[i];
    }
    return *this;
}
tem::mat2x2& tem::mat2x2::operator-=(const tem::mat2x2& other) {
    for(int i = 0; i < 4; i++) {
        this->mat[i] -= other.mat[i];
    }
    return *this;
}
tem::mat2x2& tem::mat2x2::operator*=(const tem::mat2x2& other) {
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            this->mat[i + j * 2] =
                this->mat[j * 2] * other.mat[j + i] +
                this->mat[j * 2 + 1] * other.mat[j + 2 + i];
        }
    }
    
    return *this;
}
tem::mat2x2& tem::mat2x2::operator*=(const float other) {
    for(int i = 0; i < 4; i++) {
        this->mat[i] *= other;
    }
    
    return *this;
}
tem::mat2x2& tem::mat2x2::operator/=(const float other) {
    for(int i = 0; i < 4; i++) {
        this->mat[i] /= other;
    }
    
    return *this;
}
tem::mat2x2 tem::mat2x2::operator+(const tem::mat2x2& other) {
    tem::mat2x2 temp;
    for(int i = 0; i < 4; i++) {
        temp.mat[i] = this->mat[i] + other.mat[i];
    }
    return temp;
}
tem::mat2x2 tem::mat2x2::operator-(const tem::mat2x2& other) {
    tem::mat2x2 temp;
    for(int i = 0; i < 4; i++) {
        temp.mat[i] = this->mat[i] - other.mat[i];
    }
    return temp;
}
tem::mat2x2 tem::mat2x2::operator*(const tem::mat2x2& other) {
    tem::mat2x2 temp;
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            temp.mat[i + j * 2] =
                this->mat[j * 2] * other.mat[i] +
                this->mat[j * 2 + 1] * other.mat[2 + i];
        }
    }
    
    return temp;
}
tem::vec2 tem::mat2x2::operator*(const tem::vec2& other) {
    return tem::vec2 {
        other.x * this->mat[0] + other.y * this->mat[1],
        other.x * this->mat[2] + other.y * this->mat[3]
    };
}
tem::mat2x2 tem::mat2x2::operator*(const float other) {
    tem::mat2x2 temp = tem::mat2x2(*this);
    
    for(int i = 0; i < 4; i++) {
        temp.mat[i] *= 2;
    }
    
    return temp;
}
tem::mat2x2 tem::mat2x2::operator/(const float other) {
    tem::mat2x2 temp = tem::mat2x2(*this);
    
    for(int i = 0; i < 4; i++) {
        temp.mat[i] /= 2;
    }
    
    return temp;
}


/* mat3x3 =================================================================== */

tem::mat3x3::mat3x3() : mat{ } {
}
tem::mat3x3::mat3x3(const float initValue) : mat{ }{
    for(int i = 0; i < 3; i++)
        this->mat[i+3*i] = initValue;
}
tem::mat3x3::mat3x3(const float mat[9]) {
    for(int i = 0; i < 9; i++)
        this->mat[i] = mat[i];
}
tem::mat3x3::mat3x3(const tem::mat3x3& other) {
    for(int i = 0; i < 9; i++)
        this->mat[i] = other.mat[i];
}
void tem::mat3x3::translate(float x, float y) {
    this->mat[2] = x;
    this->mat[5] = y;
}
void tem::mat3x3::scale(float sx, float sy) {
    this->mat[0] = sx;
    this->mat[4] = sy;
}
void tem::mat3x3::rotate(float angle) {
    this->mat[0] = cosf(angle);
    this->mat[1] = -sinf(angle);
    this->mat[3] = sinf(angle);
    this->mat[4] = cosf(angle);
}
tem::mat3x3 tem::mat3x3::transpose() {
    mat3x3 mat;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i + j * 3] = this->mat[j + i * 3];
        }
    }
    
    return mat;
}
tem::mat3x3 tem::mat3x3::inverse() {
    mat3x3 mat = mat3x3::Null();
    
    float det = this->determinant();
    if(det == 0) return mat;
    
    float invdet = 1.f / det;
    
    mat[0 + 0 * 3] = (this->mat[1 + 1 * 3] * this->mat[2 + 2 * 3] - this->mat[2 + 1 * 3] * this->mat[1 + 2 * 3]) * invdet;
    mat[0 + 1 * 3] = (this->mat[0 + 2 * 3] * this->mat[2 + 1 * 3] - this->mat[0 + 1 * 3] * this->mat[2 + 2 * 3]) * invdet;
    mat[0 + 2 * 3] = (this->mat[0 + 1 * 3] * this->mat[1 + 2 * 3] - this->mat[0 + 2 * 3] * this->mat[1 + 1 * 3]) * invdet;
    mat[1 + 0 * 3] = (this->mat[1 + 2 * 3] * this->mat[2 + 0 * 3] - this->mat[1 + 0 * 3] * this->mat[2 + 2 * 3]) * invdet;
    mat[1 + 1 * 3] = (this->mat[0 + 0 * 3] * this->mat[2 + 2 * 3] - this->mat[0 + 2 * 3] * this->mat[2 + 0 * 3]) * invdet;
    mat[1 + 2 * 3] = (this->mat[1 + 0 * 3] * this->mat[0 + 2 * 3] - this->mat[0 + 0 * 3] * this->mat[1 + 2 * 3]) * invdet;
    mat[2 + 0 * 3] = (this->mat[1 + 0 * 3] * this->mat[2 + 1 * 3] - this->mat[2 + 0 * 3] * this->mat[1 + 1 * 3]) * invdet;
    mat[2 + 1 * 3] = (this->mat[2 + 0 * 3] * this->mat[0 + 1 * 3] - this->mat[0 + 0 * 3] * this->mat[2 + 1 * 3]) * invdet;
    mat[2 + 2 * 3] = (this->mat[0 + 0 * 3] * this->mat[1 + 1 * 3] - this->mat[1 + 0 * 3] * this->mat[0 + 1 * 3]) * invdet;
    
    
    return mat;
}
float& tem::mat3x3::operator[](int index) {
    return this->mat[index];
}
tem::mat3x3& tem::mat3x3::operator=(const tem::mat3x3& other) {
    for(int i = 0; i < 9; i++)
        this->mat[i] = other.mat[i];
    return *this;
}
tem::mat3x3& tem::mat3x3::operator+=(const tem::mat3x3& other) {
    for(int i = 0; i < 9; i++) {
        this->mat[i] += other.mat[i];
    }
    return *this;
}
tem::mat3x3& tem::mat3x3::operator-=(const tem::mat3x3& other) {
    for(int i = 0; i < 9; i++) {
        this->mat[i] -= other.mat[i];
    }
    return *this;
}
tem::mat3x3& tem::mat3x3::operator*=(const tem::mat3x3& other) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            this->mat[i + j * 3] =
                this->mat[j * 3] * other.mat[i] +
                this->mat[j * 3 + 1] * other.mat[3 + i] +
                this->mat[j * 3 + 2] * other.mat[6 + i];
        }
    }
    return *this;
}
tem::mat3x3& tem::mat3x3::operator*=(const float other) {
    for(int i = 0; i < 9; i++) {
        this->mat[i] *= other;
    }
    
    return *this;
}
tem::mat3x3& tem::mat3x3::operator/=(const float other) {
    for(int i = 0; i < 9; i++) {
        this->mat[i] /= other;
    }
    
    return *this;
}
tem::mat3x3 tem::mat3x3::operator+(const tem::mat3x3& other) {
    tem::mat3x3 temp;
    for(int i = 0; i < 9; i++) {
        temp.mat[i] = this->mat[i] + other.mat[i];
    }
    return temp;
}
tem::mat3x3 tem::mat3x3::operator-(const tem::mat3x3& other) {
    tem::mat3x3 temp;
    for(int i = 0; i < 9; i++) {
        temp.mat[i] = this->mat[i] - other.mat[i];
    }
    return temp;
}
tem::mat3x3 tem::mat3x3::operator*(const tem::mat3x3& other) {
    tem::mat3x3 temp;
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            temp.mat[i + j * 3] =
                this->mat[j * 3] * other.mat[i] +
                this->mat[j * 3 + 1] * other.mat[3 + i] +
                this->mat[j * 3 + 2] * other.mat[6 + i];
        }
    }
    
    return temp;
}
tem::vec3 tem::mat3x3::operator*(const tem::vec3& other) {
    return tem::vec3 {
        other.x * this->mat[0] + other.y * this->mat[1] + other.z * this->mat[2],
        other.x * this->mat[3] + other.y * this->mat[4] + other.z * this->mat[5],
        other.x * this->mat[6] + other.y * this->mat[7] + other.z * this->mat[8]
    };
}
tem::mat3x3 tem::mat3x3::operator*(const float other) {
    tem::mat3x3 temp = tem::mat3x3(*this);
    
    for(int i = 0; i < 4; i++) {
        temp.mat[i] *= other;
    }
    
    return temp;
}
tem::mat3x3 tem::mat3x3::operator/(const float other) {
    tem::mat3x3 temp = tem::mat3x3(*this);
    
    for(int i = 0; i < 4; i++) {
        temp.mat[i] /= other;
    }
    
    return temp;
}


/* tem::mat4x4 =================================================================== */

tem::mat4x4::mat4x4() : mat{ }{
}
tem::mat4x4::mat4x4(const float initValue) : mat{ } {
    for(int i = 0; i < 4; i++) {
        this->mat[i+4*i] = initValue;
    }
}
tem::mat4x4::mat4x4(const float mat[16]) {
    for(int i = 0; i < 16; i++)
        this->mat[i] = mat[i];
}
tem::mat4x4::mat4x4(const tem::mat4x4& other) {
    for(int i = 0; i < 16; i++)
        this->mat[i] = other.mat[i];
}
void tem::mat4x4::translate(float x, float y, float z) {
    this->mat[3] = x;
    this->mat[7] = y;
    this->mat[11] = z;
}
void tem::mat4x4::scale(float sx, float sy, float sz) {
    this->mat[0] = sx;
    this->mat[5] = sy;
    this->mat[10] = sz;
}
void tem::mat4x4::rotate(float angle, vec3 rotationAxis) {
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    this->mat[0] = cosAngle + rotationAxis.x * rotationAxis.x * (1 - cosAngle);
    this->mat[1] = rotationAxis.x * rotationAxis.y * (1 - cosAngle) - rotationAxis.z * sinAngle;
    this->mat[2] = rotationAxis.x * rotationAxis.z * (1 - cosAngle) + rotationAxis.y * sinAngle;
    this->mat[4] = rotationAxis.y * rotationAxis.x * (1 - cosAngle) + rotationAxis.z * sinAngle;
    this->mat[5] = cosAngle + rotationAxis.y * rotationAxis.y * (1 - cosAngle);
    this->mat[6] = rotationAxis.y * rotationAxis.z * (1 - cosAngle) - rotationAxis.x * sinAngle;
    this->mat[8] = rotationAxis.z * rotationAxis.x * (1 - cosAngle) - rotationAxis.y * sinAngle;
    this->mat[9] = rotationAxis.z * rotationAxis.y * (1 - cosAngle) + rotationAxis.x * sinAngle;
    this->mat[10] = cosAngle + rotationAxis.z * rotationAxis.z * (1 - cosAngle);
}
tem::mat4x4 tem::mat4x4::transpose() {
    mat4x4 mat;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i + j * 4] = this->mat[j + i * 4];
        }
    }
    
    return mat;
}
tem::mat4x4 tem::mat4x4::inverse() {
    mat4x4 mat = mat4x4::Null();
    
    float det = this->determinant();
    if(det == 0) return mat;
    
    float invdet = 1.f / det;
    
    mat[0] = (this->mat[5]  * this->mat[10] * this->mat[15] -
             this->mat[5]  * this->mat[11] * this->mat[14] -
             this->mat[9]  * this->mat[6]  * this->mat[15] +
             this->mat[9]  * this->mat[7]  * this->mat[14] +
             this->mat[13] * this->mat[6]  * this->mat[11] -
             this->mat[13] * this->mat[7]  * this->mat[10]) * invdet;

    mat[4] = (-this->mat[4]  * this->mat[10] * this->mat[15] +
              this->mat[4]  * this->mat[11] * this->mat[14] +
              this->mat[8]  * this->mat[6]  * this->mat[15] -
              this->mat[8]  * this->mat[7]  * this->mat[14] -
              this->mat[12] * this->mat[6]  * this->mat[11] +
              this->mat[12] * this->mat[7]  * this->mat[10]) * invdet;

    mat[8] = (this->mat[4]  * this->mat[9] * this->mat[15] -
             this->mat[4]  * this->mat[11] * this->mat[13] -
             this->mat[8]  * this->mat[5] * this->mat[15] +
             this->mat[8]  * this->mat[7] * this->mat[13] +
             this->mat[12] * this->mat[5] * this->mat[11] -
             this->mat[12] * this->mat[7] * this->mat[9]) * invdet;

    mat[12] = (-this->mat[4]  * this->mat[9] * this->mat[14] +
               this->mat[4]  * this->mat[10] * this->mat[13] +
               this->mat[8]  * this->mat[5] * this->mat[14] -
               this->mat[8]  * this->mat[6] * this->mat[13] -
               this->mat[12] * this->mat[5] * this->mat[10] +
               this->mat[12] * this->mat[6] * this->mat[9]) * invdet;

    mat[1] = (-this->mat[1]  * this->mat[10] * this->mat[15] +
              this->mat[1]  * this->mat[11] * this->mat[14] +
              this->mat[9]  * this->mat[2] * this->mat[15] -
              this->mat[9]  * this->mat[3] * this->mat[14] -
              this->mat[13] * this->mat[2] * this->mat[11] +
              this->mat[13] * this->mat[3] * this->mat[10]) * invdet;

    mat[5] = (this->mat[0]  * this->mat[10] * this->mat[15] -
             this->mat[0]  * this->mat[11] * this->mat[14] -
             this->mat[8]  * this->mat[2] * this->mat[15] +
             this->mat[8]  * this->mat[3] * this->mat[14] +
             this->mat[12] * this->mat[2] * this->mat[11] -
             this->mat[12] * this->mat[3] * this->mat[10]) * invdet;

    mat[9] = (-this->mat[0]  * this->mat[9] * this->mat[15] +
              this->mat[0]  * this->mat[11] * this->mat[13] +
              this->mat[8]  * this->mat[1] * this->mat[15] -
              this->mat[8]  * this->mat[3] * this->mat[13] -
              this->mat[12] * this->mat[1] * this->mat[11] +
              this->mat[12] * this->mat[3] * this->mat[9]) * invdet;

    mat[13] = (this->mat[0]  * this->mat[9] * this->mat[14] -
              this->mat[0]  * this->mat[10] * this->mat[13] -
              this->mat[8]  * this->mat[1] * this->mat[14] +
              this->mat[8]  * this->mat[2] * this->mat[13] +
              this->mat[12] * this->mat[1] * this->mat[10] -
              this->mat[12] * this->mat[2] * this->mat[9]) * invdet;

    mat[2] = (this->mat[1]  * this->mat[6] * this->mat[15] -
             this->mat[1]  * this->mat[7] * this->mat[14] -
             this->mat[5]  * this->mat[2] * this->mat[15] +
             this->mat[5]  * this->mat[3] * this->mat[14] +
             this->mat[13] * this->mat[2] * this->mat[7] -
             this->mat[13] * this->mat[3] * this->mat[6]) * invdet;

    mat[6] = (-this->mat[0]  * this->mat[6] * this->mat[15] +
              this->mat[0]  * this->mat[7] * this->mat[14] +
              this->mat[4]  * this->mat[2] * this->mat[15] -
              this->mat[4]  * this->mat[3] * this->mat[14] -
              this->mat[12] * this->mat[2] * this->mat[7] +
              this->mat[12] * this->mat[3] * this->mat[6]) * invdet;

    mat[10] = (this->mat[0]  * this->mat[5] * this->mat[15] -
              this->mat[0]  * this->mat[7] * this->mat[13] -
              this->mat[4]  * this->mat[1] * this->mat[15] +
              this->mat[4]  * this->mat[3] * this->mat[13] +
              this->mat[12] * this->mat[1] * this->mat[7] -
              this->mat[12] * this->mat[3] * this->mat[5]) * invdet;

    mat[14] = (-this->mat[0]  * this->mat[5] * this->mat[14] +
               this->mat[0]  * this->mat[6] * this->mat[13] +
               this->mat[4]  * this->mat[1] * this->mat[14] -
               this->mat[4]  * this->mat[2] * this->mat[13] -
               this->mat[12] * this->mat[1] * this->mat[6] +
               this->mat[12] * this->mat[2] * this->mat[5]) * invdet;

    mat[3] = (-this->mat[1] * this->mat[6] * this->mat[11] +
              this->mat[1] * this->mat[7] * this->mat[10] +
              this->mat[5] * this->mat[2] * this->mat[11] -
              this->mat[5] * this->mat[3] * this->mat[10] -
              this->mat[9] * this->mat[2] * this->mat[7] +
              this->mat[9] * this->mat[3] * this->mat[6]) * invdet;

    mat[7] = (this->mat[0] * this->mat[6] * this->mat[11] -
             this->mat[0] * this->mat[7] * this->mat[10] -
             this->mat[4] * this->mat[2] * this->mat[11] +
             this->mat[4] * this->mat[3] * this->mat[10] +
             this->mat[8] * this->mat[2] * this->mat[7] -
             this->mat[8] * this->mat[3] * this->mat[6]) * invdet;

    mat[11] = (-this->mat[0] * this->mat[5] * this->mat[11] +
               this->mat[0] * this->mat[7] * this->mat[9] +
               this->mat[4] * this->mat[1] * this->mat[11] -
               this->mat[4] * this->mat[3] * this->mat[9] -
               this->mat[8] * this->mat[1] * this->mat[7] +
               this->mat[8] * this->mat[3] * this->mat[5]) * invdet;

    mat[15] = (this->mat[0] * this->mat[5] * this->mat[10] -
              this->mat[0] * this->mat[6] * this->mat[9] -
              this->mat[4] * this->mat[1] * this->mat[10] +
              this->mat[4] * this->mat[2] * this->mat[9] +
              this->mat[8] * this->mat[1] * this->mat[6] -
              this->mat[8] * this->mat[2] * this->mat[5]) * invdet;
    
    return mat;
}
float& tem::mat4x4::operator[](int index) {
    return this->mat[index];
}
tem::mat4x4& tem::mat4x4::operator=(const tem::mat4x4& other) {
    for(int i = 0; i < 16; i++)
        this->mat[i] = other.mat[i];
    return *this;
}
tem::mat4x4& tem::mat4x4::operator+=(const tem::mat4x4& other) {
    for(int i = 0; i < 16; i++) {
        this->mat[i] += other.mat[i];
    }
    return *this;
}
tem::mat4x4& tem::mat4x4::operator-=(const tem::mat4x4& other) {
    for(int i = 0; i < 16; i++) {
        this->mat[i] -= other.mat[i];
    }
    return *this;
}
tem::mat4x4& tem::mat4x4::operator*=(const tem::mat4x4& other) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            this->mat[i + j * 4] =
                this->mat[j * 4] * other.mat[i] +
                this->mat[j * 4 + 1] * other.mat[4 + i] +
                this->mat[j * 4 + 2] * other.mat[8 + i] +
                this->mat[j * 4 + 3] * other.mat[12 + i];
        }
    }
    return *this;
}
tem::mat4x4& tem::mat4x4::operator*=(const float other) {
    for(int i = 0; i < 16; i++) {
        this->mat[i] *= other;
    }
    
    return *this;
}
tem::mat4x4& tem::mat4x4::operator/=(const float other) {
    for(int i = 0; i < 16; i++) {
        this->mat[i] /= other;
    }
    
    return *this;
}
tem::mat4x4 tem::mat4x4::operator+(const tem::mat4x4& other) {
    tem::mat4x4 temp;
    for(int i = 0; i < 16; i++) {
        temp.mat[i] = this->mat[i] + other.mat[i];
    }
    return temp;
}
tem::mat4x4 tem::mat4x4::operator-(const tem::mat4x4& other) {
    tem::mat4x4 temp;
    for(int i = 0; i < 16; i++) {
        temp.mat[i] = this->mat[i] - other.mat[i];
    }
    return temp;
}
tem::mat4x4 tem::mat4x4::operator*(const tem::mat4x4& other) {
    tem::mat4x4 temp;
    
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            temp.mat[i + j * 4] =
                this->mat[j * 4] * other.mat[i] +
                this->mat[j * 4 + 1] * other.mat[4 + i] +
                this->mat[j * 4 + 2] * other.mat[8 + i] +
                this->mat[j * 4 + 3] * other.mat[12 + i];
        }
    }
    
    return temp;
}
tem::vec4 tem::mat4x4::operator*(const tem::vec4& other) {
    return tem::vec4 {
        other.x * this->mat[0] + other.y * this->mat[1] + other.z * this->mat[2] + other.w * this->mat[3],
        other.x * this->mat[4] + other.y * this->mat[5] + other.z * this->mat[6] + other.w * this->mat[7],
        other.x * this->mat[8] + other.y * this->mat[9] + other.z * this->mat[10] + other.w * this->mat[11],
        other.x * this->mat[12] + other.y * this->mat[13] + other.z * this->mat[14] + other.w * this->mat[15],
    };
}
tem::mat4x4 tem::mat4x4::operator*(const float other) {
    tem::mat4x4 temp = tem::mat4x4(*this);
    
    for(int i = 0; i < 16; i++) {
        temp.mat[i] *= other;
    }
    
    return temp;
}
tem::mat4x4 tem::mat4x4::operator/(const float other) {
    tem::mat4x4 temp = tem::mat4x4(*this);
    
    for(int i = 0; i < 16; i++) {
        temp.mat[i] /= other;
    }
    
    return temp;
}






/*
 tem::vec3& tem::vec3::operator=(const tem::vec3& other) { }
tem::vec3 tem::vec3::operator+(const tem::vec3& other) { }
tem::vec3 tem::vec3::operator-(const tem::vec3& other) { }
tem::vec3 tem::vec3::operator*(const tem::vec3& other) { }
tem::vec3 tem::vec3::operator*(const tem::mat3x3& other) { }
tem::vec3 tem::vec3::operator/(const tem::vec3& other) { }

tem::vec4& tem::vec4::operator=(const tem::vec4& other) { }
tem::vec4 tem::vec4::operator+(const tem::vec4& other) { }
tem::vec4 tem::vec4::operator-(const tem::vec4& other) { }
tem::vec4 tem::vec4::operator*(const tem::vec4& other) { }
tem::vec4 tem::vec4::operator*(const tem::mat4x4& other) { }
tem::vec4 tem::vec4::operator/(const tem::vec4& other) { }


tem::mat2x2& tem::mat2x2::operator=(const tem::mat2x2& other) { }
tem::mat2x2 tem::mat2x2::operator+(const tem::mat2x2& other) { }
tem::mat2x2 tem::mat2x2::operator-(const tem::mat2x2& other) { }
tem::mat2x2 tem::mat2x2::operator*(const tem::mat2x2& other) { }

tem::mat3x3& tem::mat3x3::operator=(const tem::mat3x3& other) { }
tem::mat3x3 tem::mat3x3::operator+(const tem::mat3x3& other) { }
tem::mat3x3 tem::mat3x3::operator-(const tem::mat3x3& other) { }
tem::mat3x3 tem::mat3x3::operator*(const tem::mat3x3& other) { }

tem::mat4x4& tem::mat4x4::operator=(const tem::mat4x4& other)
tem::mat4x4 tem::mat4x4::operator+(const tem::mat4x4& other) { }
tem::mat4x4 tem::mat4x4::operator-(const tem::mat4x4& other) { }
tem::mat4x4 tem::mat4x4::operator*(const tem::mat4x4& other) { }
*/

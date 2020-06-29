//
//  tensorMath.hpp
//  Voksel
//
//  Created by Marat Isaw on 21.06.20.
//  Copyright © 2020 Marat Isaw. All rights reserved.
//

#ifndef TENSOR_MATH_HPP
#define TENSOR_MATH_HPP
#include <cmath>

namespace tem {
    class mat2x2;
    class mat3x3;
    class mat4x4;


    class vec2 {
    public:
        float x;
        float y;
        
        inline float length() {
            return sqrt((x * x) + (y * y));
        }
        
        vec2& operator=(const vec2& other);
        vec2& operator+=(const vec2& other);
        vec2& operator-=(const vec2& other);
        vec2& operator*=(const float other);
        vec2& operator/=(const float other);
        vec2 operator+(const vec2& other);
        vec2 operator-(const vec2& other);
        float operator*(const vec2& other);
        vec2 operator*(const float other);
        vec2 operator/(const float other);
    };
    class vec3 {
    public:
        float x;
        float y;
        float z;

        inline float length() {
            return sqrt((x * x) + (y * y) + (z * z));
        }

        vec3& operator=(const vec3& other);
        vec3& operator+=(const vec3& other);
        vec3& operator-=(const vec3& other);
        vec3& operator*=(const float other);
        vec3& operator/=(const float other);
        vec3 operator+(const vec3& other);
        vec3 operator-(const vec3& other);
        float operator*(const vec3& other);
        vec3 operator*(const float other);
        vec3 operator/(const float other);
    };
    class vec4 {
    public:
        float x;
        float y;
        float z;
        float w;

        inline float length() {
            return sqrt((x * x) + (y * y) + (z * z) + (w * w));
        }
        
        vec4& operator=(const vec4& other);
        vec4& operator+=(const vec4& other);
        vec4& operator-=(const vec4& other);
        vec4& operator*=(const float other);
        vec4& operator/=(const float other);
        vec4 operator+(const vec4& other);
        vec4 operator-(const vec4& other);
        float operator*(const vec4& other);
        vec4 operator*(const float other);
        vec4 operator/(const float other);
    };

    // TODO: make base class for matrices


    class mat2x2 {
    public:
        float mat[4];
        
        mat2x2();
        mat2x2(const float initValue);
        mat2x2(const mat2x2& other);
        mat2x2(const float mat[4]);
        
        void translate(float x);
        void scale(float sx);
        void rotate(float angle);
        
        mat2x2 transpose();
        mat2x2 inverse();
        inline float determinant() {
            return mat[0] * mat[3] - mat[1] * mat[2];
        }
        inline float GetValue(int row, int column) {
            return mat[column + row * 2];
        }
        inline static mat2x2 Identity() {
            return { (float[]) {
                1.f, 0.f,
                0.f, 1.f,
            } };
        }
        inline static mat2x2 Null() {
            return { };
        }
        
        float& operator[](int index);
        mat2x2& operator=(const mat2x2& other);
        mat2x2& operator+=(const mat2x2& other);
        mat2x2& operator-=(const mat2x2& other);
        mat2x2& operator*=(const mat2x2& other);
        mat2x2& operator*=(const float other);
        mat2x2& operator/=(const float other);
        mat2x2 operator+(const mat2x2& other);
        mat2x2 operator-(const mat2x2& other);
        mat2x2 operator*(const mat2x2& other);
        vec2 operator*(const vec2& other);
        mat2x2 operator*(const float other);
        mat2x2 operator/(const float other);
    };
    class mat3x3 {
    public:
        float mat[9];
        
        mat3x3();
        mat3x3(const float initValue);
        mat3x3(const mat3x3& other);
        mat3x3(const float mat[9]);
        
        void translate(float x, float y);
        void scale(float sx, float sy);
        void rotate(float angle);

        mat3x3 transpose();
        mat3x3 inverse();
        inline float determinant() {
            return mat[0] * (mat[4] * mat[8] - mat[5] * mat[7]) -
                   mat[1] * (mat[3] * mat[8] - mat[5] * mat[6]) +
                   mat[2] * (mat[3] * mat[7] - mat[4] * mat[6]);
        }
        inline float GetValue(int row, int column) {
            return mat[column + row * 3];
        }
        inline static mat3x3 Identity() {
            return { (float[]) {
                1.f, 0.f, 0.f,
                0.f, 1.f, 0.f,
                0.f, 0.f, 1.f,
            } };
        }
        inline static mat3x3 Null() {
            return { };
        }

        float& operator[](int index);
        mat3x3& operator=(const mat3x3& other);
        mat3x3& operator+=(const mat3x3& other);
        mat3x3& operator-=(const mat3x3& other);
        mat3x3& operator*=(const mat3x3& other);
        mat3x3& operator*=(const float other);
        mat3x3& operator/=(const float other);
        mat3x3 operator+(const mat3x3& other);
        mat3x3 operator-(const mat3x3& other);
        mat3x3 operator*(const mat3x3& other);
        vec3 operator*(const vec3& other);
        mat3x3 operator*(const float other);
        mat3x3 operator/(const float other);
    };
    class mat4x4 {
    public:
        float mat[16];
        
        mat4x4();
        mat4x4(const float initValue);
        mat4x4(const mat4x4& other);
        mat4x4(const float mat[16]);
        
        void translate(float x, float y, float z);
        void scale(float sx, float sy, float sz);
        void rotate(float angle, vec3 rotationAxis);
        
        mat4x4 transpose();
        mat4x4 inverse();
        inline float determinant() {
            return  mat[0 + 3 * 4] * mat[1 + 2 * 4] * mat[2 + 1 * 4] * mat[3 + 0 * 4] - mat[0 + 2 * 4] * mat[1 + 3 * 4] * mat[2 + 1 * 4] * mat[3 + 0 * 4] -
                    mat[0 + 3 * 4] * mat[1 + 1 * 4] * mat[2 + 2 * 4] * mat[3 + 0 * 4] + mat[0 + 1 * 4] * mat[1 + 3 * 4] * mat[2 + 2 * 4] * mat[3 + 0 * 4] +
                    mat[0 + 2 * 4] * mat[1 + 1 * 4] * mat[2 + 3 * 4] * mat[3 + 0 * 4] - mat[0 + 1 * 4] * mat[1 + 2 * 4] * mat[2 + 3 * 4] * mat[3 + 0 * 4] -
                    mat[0 + 3 * 4] * mat[1 + 2 * 4] * mat[2 + 0 * 4] * mat[3 + 1 * 4] + mat[0 + 2 * 4] * mat[1 + 3 * 4] * mat[2 + 0 * 4] * mat[3 + 1 * 4] +
                    mat[0 + 3 * 4] * mat[1 + 0 * 4] * mat[2 + 2 * 4] * mat[3 + 1 * 4] - mat[0 + 0 * 4] * mat[1 + 3 * 4] * mat[2 + 2 * 4] * mat[3 + 1 * 4] -
                    mat[0 + 2 * 4] * mat[1 + 0 * 4] * mat[2 + 3 * 4] * mat[3 + 1 * 4] + mat[0 + 0 * 4] * mat[1 + 2 * 4] * mat[2 + 3 * 4] * mat[3 + 1 * 4] +
                    mat[0 + 3 * 4] * mat[1 + 1 * 4] * mat[2 + 0 * 4] * mat[3 + 2 * 4] - mat[0 + 1 * 4] * mat[1 + 3 * 4] * mat[2 + 0 * 4] * mat[3 + 2 * 4] -
                    mat[0 + 3 * 4] * mat[1 + 0 * 4] * mat[2 + 1 * 4] * mat[3 + 2 * 4] + mat[0 + 0 * 4] * mat[1 + 3 * 4] * mat[2 + 1 * 4] * mat[3 + 2 * 4] +
                    mat[0 + 1 * 4] * mat[1 + 0 * 4] * mat[2 + 3 * 4] * mat[3 + 2 * 4] - mat[0 + 0 * 4] * mat[1 + 1 * 4] * mat[2 + 3 * 4] * mat[3 + 2 * 4] -
                    mat[0 + 2 * 4] * mat[1 + 1 * 4] * mat[2 + 0 * 4] * mat[3 + 3 * 4] + mat[0 + 1 * 4] * mat[1 + 2 * 4] * mat[2 + 0 * 4] * mat[3 + 3 * 4] +
                    mat[0 + 2 * 4] * mat[1 + 0 * 4] * mat[2 + 1 * 4] * mat[3 + 3 * 4] - mat[0 + 0 * 4] * mat[1 + 2 * 4] * mat[2 + 1 * 4] * mat[3 + 3 * 4] -
                    mat[0 + 1 * 4] * mat[1 + 0 * 4] * mat[2 + 2 * 4] * mat[3 + 3 * 4] + mat[0 + 0 * 4] * mat[1 + 1 * 4] * mat[2 + 2 * 4] * mat[3 + 3 * 4];
        }

        inline float GetValue(int row, int column) {
            return mat[column + row * 4];
        }
        inline static mat4x4 Identity() {
            return { (float[]) {
                1.f, 0.f, 0.f, 0.f,
                0.f, 1.f, 0.f, 0.f,
                0.f, 0.f, 1.f, 0.f,
                0.f, 0.f, 0.f, 1.f,
            } };
        }
        inline static mat4x4 Null() {
            return { };
        }

        float& operator[](int index);
        mat4x4& operator=(const mat4x4& other);
        mat4x4& operator+=(const mat4x4& other);
        mat4x4& operator-=(const mat4x4& other);
        mat4x4& operator*=(const mat4x4& other);
        mat4x4& operator*=(const float other);
        mat4x4& operator/=(const float other);
        mat4x4 operator+(const mat4x4& other);
        mat4x4 operator-(const mat4x4& other);
        mat4x4 operator*(const mat4x4& other);
        vec4 operator*(const vec4& other);
        mat4x4 operator*(const float other);
        mat4x4 operator/(const float other);
    };
};

#endif /* TENSOR_MATH_HPP */

#pragma once

#include "Vector.h"

namespace sr {
    template<typename T>
    struct Matrix4x4 {
        T m[16];
        Matrix4x4(): m{} {}
        template<typename... L>
        Matrix4x4(L... nums): m{nums...} {}

        static Matrix4x4<T> Zero();
        static Matrix4x4<T> Identity();
        Matrix4x4<T> operator+(const Matrix4x4<T>& mat) const;
        Matrix4x4<T> operator-(const Matrix4x4<T>& mat) const;
        Vector4<T> operator*(const Vector4<T>& vec) const;
        Matrix4x4<T> operator*(const Matrix4x4<T>& ma) const;
        Matrix4x4<T>& operator+=(const Matrix4x4<T>& mat);
        Matrix4x4<T>& operator-=(const Matrix4x4<T>& mat);
        Matrix4x4<T>& operator*=(const Matrix4x4<T>& ma);
    };

    template<typename T>
    Matrix4x4<T> Matrix4x4<T>::Zero() {
        return Matrix4x4<T>{};
    }
    template<typename T>
    Matrix4x4<T> Matrix4x4<T>::Identity() {
        return Matrix4x4<T> {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    }
    template<typename T>
    Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4<T>& mat) const {
        return Matrix4x4<T> {
            m[ 0] + mat.m[ 0], m[ 1] + mat.m[ 1], m[ 2] + mat.m[ 2], m[ 3] + mat.m[ 3],
            m[ 4] + mat.m[ 4], m[ 5] + mat.m[ 5], m[ 6] + mat.m[ 6], m[ 7] + mat.m[ 7],
            m[ 8] + mat.m[ 8], m[ 9] + mat.m[ 9], m[10] + mat.m[10], m[11] + mat.m[11],
            m[12] + mat.m[12], m[13] + mat.m[13], m[14] + mat.m[14], m[15] + mat.m[15]
        };
    }
    template<typename T>
    Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4<T>& mat) const {
        return Matrix4x4<T> {
            m[ 0] - mat.m[ 0], m[ 1] - mat.m[ 1], m[ 2] - mat.m[ 2], m[ 3] - mat.m[ 3],
            m[ 4] - mat.m[ 4], m[ 5] - mat.m[ 5], m[ 6] - mat.m[ 6], m[ 7] - mat.m[ 7],
            m[ 8] - mat.m[ 8], m[ 9] - mat.m[ 9], m[10] - mat.m[10], m[11] - mat.m[11],
            m[12] - mat.m[12], m[13] - mat.m[13], m[14] - mat.m[14], m[15] - mat.m[15]
        };
    }
    template<typename T>
    Vector4<T> Matrix4x4<T>::operator*(const Vector4<T>& vec) const {
        return Vector4<T> {
            m[ 0] * vec.x + m[ 1] * vec.y + m[ 2] * vec.z + m[ 3] * vec.w,
            m[ 4] * vec.x + m[ 5] * vec.y + m[ 6] * vec.z + m[ 7] * vec.w,
            m[ 8] * vec.x + m[ 9] * vec.y + m[10] * vec.z + m[11] * vec.w,
            m[12] * vec.x + m[13] * vec.y + m[14] * vec.z + m[15] * vec.w
        };
    }
    template<typename T>
    Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& ma) const {
        Matrix4x4<T> ret{};
        for (int y = 0; y < 4; ++y)
            for (int x = 0; x < 4; ++x)
                for (int k = 0; k < 4; ++k)
                    ret[y * 4 + x] += m[y * 4 + k] * ma.m[k * 4 + x];
        return ret;
    }
    template<typename T>
    Matrix4x4<T>& Matrix4x4<T>::operator+=(const Matrix4x4<T>& mat) {
        m[ 0] += mat.m[ 0]; m[ 1] += mat.m[ 1]; m[ 2] += mat.m[ 2]; m[ 3] += mat.m[ 3];
        m[ 4] += mat.m[ 4]; m[ 5] += mat.m[ 5]; m[ 6] += mat.m[ 6]; m[ 7] += mat.m[ 7];
        m[ 8] += mat.m[ 8]; m[ 9] += mat.m[ 9]; m[10] += mat.m[10]; m[11] += mat.m[11];
        m[12] += mat.m[12]; m[13] += mat.m[13]; m[14] += mat.m[14]; m[15] += mat.m[15];
        return *this;
    }
    template<typename T>
    Matrix4x4<T>& Matrix4x4<T>::operator-=(const Matrix4x4<T>& mat) {
        m[ 0] -= mat.m[ 0]; m[ 1] -= mat.m[ 1]; m[ 2] -= mat.m[ 2]; m[ 3] -= mat.m[ 3];
        m[ 4] -= mat.m[ 4]; m[ 5] -= mat.m[ 5]; m[ 6] -= mat.m[ 6]; m[ 7] -= mat.m[ 7];
        m[ 8] -= mat.m[ 8]; m[ 9] -= mat.m[ 9]; m[10] -= mat.m[10]; m[11] -= mat.m[11];
        m[12] -= mat.m[12]; m[13] -= mat.m[13]; m[14] -= mat.m[14]; m[15] -= mat.m[15];
        return *this;
    }
    template<typename T>
    Matrix4x4<T>& Matrix4x4<T>::operator*=(const Matrix4x4<T>& ma) {
        const Matrix4x4<T> ret = this->operator*(ma);
        *this = ret;
        return *this;
    }
}
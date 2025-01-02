#pragma once

#include <cmath>

#include "Vector.h"
#include "Matrix.h"

namespace sr {
    struct Math {
        static Matrix4x4<float> GetMatrixTranslate(const Vector3<float>& pos);
        static Matrix4x4<float> GetMatrixRotateX(float theta);
        static Matrix4x4<float> GetMatrixRotateY(float theta);
        static Matrix4x4<float> GetMatrixRotateZ(float theta);
        static Matrix4x4<float> GetMatrixScale(const Vector3<float>& factor);
    };

        Matrix4x4<float> Math::GetMatrixTranslate(const Vector3<float>& pos) {
            return Matrix4x4<float> {
                1.0f, 0.0f, 0.0f, pos.x,
                0.0f, 1.0f, 0.0f, pos.y,
                0.0f, 0.0f, 1.0f, pos.z,
                0.0f, 0.0f, 0.0f, 1.0f
            };
        }
        Matrix4x4<float> Math::GetMatrixRotateX(float theta) {
            return Matrix4x4<float> {
                1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, std::cos(theta), -std::sin(theta), 0.0f,
                0.0f, std::sin(theta), std::cos(theta), 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            };
        }
        Matrix4x4<float> Math::GetMatrixRotateY(float theta) {
            return Matrix4x4<float> {
                std::cos(theta), 0.0f, std::sin(theta), 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                -std::sin(theta), 0.0f, std::cos(theta), 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            };
        }
        Matrix4x4<float> Math::GetMatrixRotateZ(float theta) {
            return Matrix4x4<float> {
                std::cos(theta), -std::sin(theta), 0.0f, 0.0f,
                std::sin(theta), std::cos(theta), 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            };
        }
        Matrix4x4<float> Math::GetMatrixScale(const Vector3<float>& factor) {
            return Matrix4x4<float> {
                factor.x, 0.0f, 0.0f, 0.0f,
                0.0f, factor.y, 0.0f, 0.0f,
                0.0f, 0.0f, factor.z, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            };
        }
}
#pragma once

namespace sr {

#define VECTOR_OPS_HEADER(N)\
    Vector##N<T> operator+(const Vector##N<T>& v) const;\
    Vector##N<T> operator-(const Vector##N<T>& v) const;\
    Vector##N<T> operator*(T val) const;\
    Vector##N<T> operator/(T val) const;\
    Vector##N<T>& operator+=(const Vector##N<T>& v);\
    Vector##N<T>& operator-=(const Vector##N<T>& v);\
    Vector##N<T>& operator*=(T val);\
    Vector##N<T>& operator/=(T val);\
    T operator[](int index) const;\
    T dot(const Vector##N<T>& v) const;

    template<typename T>
    struct Vector2 {
        T x, y;
        Vector2(): x(0), y(0) {}
        Vector2(T x_in, T y_in): x(x_in), y(y_in) {}
        VECTOR_OPS_HEADER(2)
    };
    template<typename T>
    struct Vector3 {
        T x, y, z;
        Vector3(): x(0), y(0), z(0) {}
        Vector3(T x_in, T y_in, T z_in): x(x_in), y(y_in), z(z_in) {}
        Vector3(const Vector2<T>& v): x(v.x), y(v.y), z(0) {}
        VECTOR_OPS_HEADER(3)
        Vector3<T> cross(const Vector3<T>& v) const;
    };
    template<typename T>
    struct Vector4 {
        T x, y, z, w;
        Vector4(): x(0), y(0), z(0), w(0) {}
        Vector4(T x_in, T y_in, T z_in, T w_in): x(x_in), y(y_in), z(z_in), w(w_in) {}
        Vector4(const Vector2<T>& v): x(v.x), y(v.y), z(0), w(0) {}
        Vector4(const Vector3<T>& v): x(v.x), y(v.y), z(v.z), w(0) {}
        VECTOR_OPS_HEADER(4)
    };

	template<typename T>
	Vector2<T> Vector2<T>::operator+(const Vector2<T>& v) const {
		return Vector2<T>(x + v.x, y + v.y);
	}
	template<typename T>
	Vector2<T> Vector2<T>::operator-(const Vector2<T>& v) const {
		return Vector2<T>(x - v.x, y - v.y);
	}
	template<typename T>
	Vector2<T> Vector2<T>::operator*(T val) const {
		return Vector2<T>(x * val, y * val);
	}
	template<typename T>
	Vector2<T> Vector2<T>::operator/(T val) const {
		return Vector2<T>(x / val, y / val);
	}
	template<typename T>
	Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& v) {
		x += v.x; y += v.y;
        return *this;
	}
	template<typename T>
	Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& v) {
		x -= v.x; y -= v.y;
        return *this;
	}
	template<typename T>
	Vector2<T>& Vector2<T>::operator*=(T val) {
		x *= val; y *= val;
        return *this;
	}
	template<typename T>
	Vector2<T>& Vector2<T>::operator/=(T val) {
		x /= val; y /= val;
        return *this;
	}
	template<typename T>
    T Vector2<T>::operator[](int index) const {
		if (index == 0) return x;
        else if (index == 1) return y;
        else return 0;
	}
	template<typename T>
    T Vector2<T>::dot(const Vector2<T>& v) const {
		return x * v.x + y * v.y;
	}


}
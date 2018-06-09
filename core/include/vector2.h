#pragma once

namespace bear { namespace core {

	template<typename T>
	struct Vector2 {
		T x;
		T y;

		Vector2(T a_x, T a_y) : x(a_x), y(a_y) { }
		Vector2() : x(0), y(0);
	};

	// Operator overloading
	template<typename T> Vector2<T> operator+(const Vector2<T> right);
	template<typename T> Vector2<T> operator-(const Vector2<T> right);
	template<typename T> Vector2<T> operator/(const Vector2<T> right);
	template<typename T> Vector2<T> operator*(const T scalar);
	template<typename T> Vector2<T>& operator+=(const Vector2<T>& right);
	template<typename T> Vector2<T>& operator-=(const Vector2<T>& right);
	
	// Define some default templates
	typedef Vector2<int> Vector2i;
	typedef Vector2<float> Vector2f;
	typedef Vector2<unsigned int> Vector2ui;

} }
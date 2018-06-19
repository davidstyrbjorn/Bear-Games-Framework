#pragma once

#include<iostream>

namespace bear { namespace core {

	template<typename T>
	struct Vector2 {
		T x;
		T y;

		Vector2(T a_x, T a_y) : x(a_x), y(a_y) { }
		Vector2() : x(0), y(0) { }

		// Operator overloading
		friend std::ostream & operator<<(std::ostream &os, const Vector2<T> &right) {
			os << "(" << right.x << ", " << right.y << ")";
			return os;
		}
		Vector2<T> operator-(const Vector2<T> right) {
			return Vector2<T>(this->x - right.x, this->y - right.y);
		}
		Vector2<T> operator+(const Vector2<T> right) {
			return Vector2<T>(this->x + right.x, this->y + right.y);
		}
		Vector2<T> operator*(const Vector2<T> right) {
			return Vector2<T>(this->x * right.x, this->y * right.y);
		}
		Vector2<T>& operator+=(const Vector2<T>& right) {
			this->x += right.x;
			this->y += right.y;
			return *this;
		}
		Vector2<T>& operator-=(const Vector2<T>& right) {
			this->x -= right.x;
			this->y -= right.y;
			return *this;
		}
		Vector2<T>& operator*=(const Vector2<T>& right) {
			this->x *= right.x;
			this->y *= right.y;
			return *this;
		}
	};
	
	// Define some default templates
	typedef Vector2<int> Vector2i;
	typedef Vector2<float> Vector2f;
	typedef Vector2<unsigned int> Vector2ui;
	typedef Vector2<double> Vector2d;
}
}
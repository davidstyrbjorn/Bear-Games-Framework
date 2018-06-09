#include"../include/vector2.h"

template<typename T>
Vector2<T> bear::core::operator+(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>(left.x + right.x, left.y + right.y);
}

template<typename T>
Vector2<T> bear::core::operator-(const Vector2<T>& left, const Vector2<T>& right)
{
	return Vector2<T>();
}

template<typename T>
Vector2<T> bear::core::operator+=(const Vector2<T>& right)
{
	return Vector2<T>();
}

template<typename T>
Vector2<T> bear::core::operator-=(const Vector2<T>& right)
{
	return Vector2<T>();
}
	

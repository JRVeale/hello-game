#include "Vector2D.h"

Vector2D::Vector2D() {
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vec) {
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}
Vector2D& Vector2D::Subtract(const Vector2D& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector2D& Vector2D::Multiply(const Vector2D& vec) {
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}
Vector2D& Vector2D::Divide(const Vector2D& vec) {
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

float Vector2D::length() {
	float squared_length = pow(x, 2) + pow(y, 2);
	return sqrtf(squared_length);
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
	Vector2D vNew = v1;
	return vNew.Add(v2);
}
Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
	Vector2D vNew = v1;
	return vNew.Subtract(v2);
}
Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
	Vector2D vNew = v1;
	return vNew.Multiply(v2);
}
Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
	Vector2D vNew = v1;
	return vNew.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
	return this->Add(vec);
}
Vector2D& Vector2D::operator-=(const Vector2D& vec) {
	return this->Subtract(vec);
}
Vector2D& Vector2D::operator*=(const Vector2D& vec) {
	return this->Multiply(vec);
}
Vector2D& Vector2D::operator/=(const Vector2D& vec) {
	return this->Divide(vec);
}

Vector2D& Vector2D::operator*(const int& i) {
	this->x *= i;
	this->y *= i;
	return *this;
}
Vector2D& Vector2D::Zero() {
	this->x = 0.0f;
	this->y = 0.0f;
	return *this;
}


std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}
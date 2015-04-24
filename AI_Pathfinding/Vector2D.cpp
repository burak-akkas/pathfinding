#include <cmath>
#include "Vector2D.h"

void Vector2D::Zero() {
	x = 0.0;
	y = 0.0;
}

bool Vector2D::isZero() {
	return (x == 0 && y == 0);
}

double Vector2D::Length() {
	return sqrt(x * x + y * y);
}

double Vector2D::LengthSq() {
	return (x * x + y * y);
}

double Vector2D::Distance(const Vector2D& v2) {
	double dif_x, dif_y;
	dif_x = v2.x - x;
	dif_y = v2.y - y;

	return (dif_y * dif_y - dif_x * dif_x);
}

void Vector2D::copy(Vector2D rhs) {
	x = rhs.x;
	y = rhs.y;
}

double Vector2D::getX() {
	return x;
}

double Vector2D::getY() {
	return y;
}

void Vector2D::setX(double t_x) {
	x = t_x;
}

void Vector2D::setY(double t_y) {
	y = t_y;
}

const Vector2D& Vector2D::operator+=(const Vector2D &rhs) {
	x += rhs.x;
	y += rhs.y;

	return *this;
}

const Vector2D& Vector2D::operator-=(const Vector2D &rhs) {
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

const Vector2D& Vector2D::operator*=(const double& rhs) {
	x *= rhs;
	y *= rhs;

	return *this;
}

const Vector2D& Vector2D::operator/= (const double& rhs) {
	x /= rhs;
	y /= rhs;

	return *this;
}

bool Vector2D::operator==(const Vector2D& rhs)const {
	if (x == rhs.x && y == rhs.y) return true;
	else return false;
}

bool Vector2D::operator!=(const Vector2D& rhs)const {
	return (x != rhs.x) || (y != rhs.y);
}
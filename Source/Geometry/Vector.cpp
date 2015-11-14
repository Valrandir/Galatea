#include "Vector.hpp"
#include "Point.hpp"
#include <math.h>

namespace Galatea
{
	namespace Geometry
	{
		const double Vector::EPSILON = .00001;

		Vector::Vector() : x{}, y{} {}
		Vector::Vector(double x, double y) : x{x}, y{y} {}

		Vector::Vector(const Vector& src) { x = src.x; y = src.y; }
		Vector& Vector::operator=(const Vector& src) { x = src.x; y = src.y; return *this; }

		Vector Vector::operator-() const { return Vector(-x, -y); }
		bool Vector::operator==(const Vector& src) const { return x == src.x && y == src.y; }

		Vector Vector::operator+(const Vector& src) const { return Vector{x + src.x, y + src.y}; }
		Vector Vector::operator-(const Vector& src) const { return Vector{x - src.x, y - src.y}; }
		Vector Vector::operator*(const Vector& src) const { return Vector{x * src.x, y * src.y}; }
		Vector Vector::operator/(const Vector& src) const { return Vector{x / src.x, y / src.y}; }

		Vector Vector::operator+(double val) const { return Vector{x + val, y + val}; }
		Vector Vector::operator-(double val) const { return Vector{x - val, y - val}; }
		Vector Vector::operator*(double val) const { return Vector{x * val, y * val}; }
		Vector Vector::operator/(double val) const { return Vector{x / val, y / val}; }

		Vector& Vector::operator+=(const Vector& src) { x += src.x, y += src.y; return *this; }
		Vector& Vector::operator-=(const Vector& src) { x -= src.x, y -= src.y; return *this; }
		Vector& Vector::operator*=(const Vector& src) { x *= src.x, y *= src.y; return *this; }
		Vector& Vector::operator/=(const Vector& src) { x /= src.x, y /= src.y; return *this; }

		Vector& Vector::operator+=(double val) { x += val, y += val; return *this; }
		Vector& Vector::operator-=(double val) { x -= val, y -= val; return *this; }
		Vector& Vector::operator*=(double val) { x *= val, y *= val; return *this; }
		Vector& Vector::operator/=(double val) { x /= val, y /= val; return *this; }

		Vector& Vector::operator++() { ++x, ++y; return *this; }
		Vector& Vector::operator--() { --x, --y; return *this; }
		Vector Vector::operator++(int) { Vector result(*this); ++x, ++y; return result; }
		Vector Vector::operator--(int) { Vector result(*this); --x, --y; return result; }

		double Vector::EpsilonZero(double value)
		{
			return fabs(value) < EPSILON ? .0 : value;
		}

		Vector& Vector::EpsilonZero()
		{
			x = EpsilonZero(x);
			y = EpsilonZero(y);
			return *this;
		}

		Vector& Vector::Normalize()
		{
			double sum = fabs(x) + fabs(y);
			if(sum) x /= sum, y /= sum;
			return *this;
		}

		double Vector::Distance(const Vector& vec) const
		{
			double dx = vec.x - x;
			double dy = vec.y - y;
			return sqrt(dx * dx + dy * dy);
		}

		Point Vector::ToPoint() const
		{
			return Point(static_cast<int>(x), static_cast<int>(y));
		}
	}
}

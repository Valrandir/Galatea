#pragma once

namespace Galatea
{
	namespace Geometry
	{
		struct Point;

		struct Vector
		{
			static const double EPSILON;
			double x, y;

			Vector();
			Vector(double x, double y);

			Vector(const Vector& src);
			Vector& operator=(const Vector& src);

			Vector operator-() const;
			bool operator==(const Vector& src) const;

			Vector operator+(const Vector& src) const;
			Vector operator-(const Vector& src) const;
			Vector operator*(const Vector& src) const;
			Vector operator/(const Vector& src) const;

			Vector operator+(double val) const;
			Vector operator-(double val) const;
			Vector operator*(double val) const;
			Vector operator/(double val) const;

			Vector& operator+=(const Vector& src);
			Vector& operator-=(const Vector& src);
			Vector& operator*=(const Vector& src);
			Vector& operator/=(const Vector& src);

			Vector& operator+=(double val);
			Vector& operator-=(double val);
			Vector& operator*=(double val);
			Vector& operator/=(double val);

			Vector& operator++();
			Vector& operator--();
			Vector operator++(int);
			Vector operator--(int);

			static double EpsilonZero(double value);
			Vector& EpsilonZero();
			Vector& Normalize();
			double Distance(const Vector& vec) const;

			Point ToPoint() const;
		};
	}
}

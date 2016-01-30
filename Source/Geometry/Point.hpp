#pragma once

namespace Galatea
{
	namespace Geometry
	{
		struct Vector;

		struct Point
		{
			int x, y;

			Point();
			Point(int x, int y);

			Point(const Point& src);
			Point& operator=(const Point& src);
			Point& operator=(int val);

			Point operator-() const;
			bool operator==(const Point& src) const;

			Point operator+(const Point& src) const;
			Point operator-(const Point& src) const;
			Point operator*(const Point& src) const;
			Point operator/(const Point& src) const;

			Point operator+(int val) const;
			Point operator-(int val) const;
			Point operator*(int val) const;
			Point operator/(int val) const;

			Point& operator+=(const Point& src);
			Point& operator-=(const Point& src);
			Point& operator*=(const Point& src);
			Point& operator/=(const Point& src);

			Point& operator+=(int val);
			Point& operator-=(int val);
			Point& operator*=(int val);
			Point& operator/=(int val);

			Point& operator++();
			Point& operator--();
			Point operator++(int);
			Point operator--(int);

			Vector ToVector() const;
		};
	}
}

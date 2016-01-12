#include "Rectangle.hpp"

namespace Galatea
{
	namespace Geometry
	{
		Rectangle::Rectangle() {}

		Rectangle::Rectangle(const Rectangle& src)
		{
			x1 = src.x1;
			y1 = src.y1;
			x2 = src.x2;
			y2 = src.y2;
		}

		Rectangle& Rectangle::operator=(const Rectangle& src)
		{
			x1 = src.x1;
			y1 = src.y1;
			x2 = src.x2;
			y2 = src.y2;
			return *this;
		}

		bool Rectangle::operator==(const Rectangle& src) const
		{
			return
				x1 == src.x1 &&
				y1 == src.y1 &&
				x2 == src.x2 &&
				y2 == src.y2;
		}

		Rectangle::Rectangle(const Point& xh1, const Point& xy2) : x1{xh1.x}, y1{xh1.y}, x2{xy2.x}, y2{xy2.y} {}

		Rectangle::Rectangle(const Point& position, const Size& size) : x1{position.x}, y1{position.y}, x2{position.x + size.x}, y2{position.y + size.y} {}

		Rectangle::Rectangle(const Geometry::Center& center, const Size& size)
		{
			Point half = size / 2;
			x1 = center.x - half.x;
			y1 = center.y - half.y;
			x2 = center.x + half.x;
			y2 = center.y + half.y;
		}

		void Rectangle::SetPosition(const Point& position)
		{
			x2 += position.x - x1;
			y2 += position.y - y1;
			x1 = position.x;
			y1 = position.y;
		}

		void Rectangle::SetCenter(const Point& center)
		{
			int hx = Width() / 2;
			int hy = Height() / 2;
			x1 = center.x - hx;
			y1 = center.y - hy;
			x2 = center.x + hx;
			y2 = center.y + hy;
		}

		void Rectangle::SetSize(const Point& size)
		{
			x2 = x1 + size.x;
			y2 = y1 + size.y;
		}

		void Rectangle::Offset(const Point& offset)
		{
			x1 += offset.x;
			y1 += offset.y;
			x2 += offset.x;
			y2 += offset.y;
		}

		bool Rectangle::Intersect(const Rectangle& src) const
		{
			return
				src.x2 >= x1 &&
				src.x1 <= x2 &&
				src.y2 >= y1 &&
				src.y1 <= y2;
		}

		int Rectangle::Width() const { return x2 - x1; }

		int Rectangle::Height() const { return y2 - y1; }

		Point Rectangle::Center() const { return Point{x1 + Width() / 2, y1 + Height() / 2}; }
	}
}

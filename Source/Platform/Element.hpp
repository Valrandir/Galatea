#pragma once
#include "../Geometry/Geometry.hpp"
#include "../Display/Display.hpp"

namespace Galatea
{
	namespace Platform
	{
		class Element
		{
			Geometry::Rectangle rect;
			const Display::Image* image;
			Display::Color color;

			public:
			Element(const Geometry::Rectangle& rect, const Display::Color& color);
			Element(const Geometry::Point& position, const Display::Image* image, const Display::Color& color);

			virtual ~Element();
			virtual void Update();
			virtual void Render(const Display::Image* target, const Geometry::Point& offset) const;

			const Geometry::Rectangle& Area() const;
		};
	}
}

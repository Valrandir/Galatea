#pragma once
#include "../Geometry/Geometry.hpp"
#include "../Display/Display.hpp"

namespace Galatea
{
	namespace Platform
	{
		using namespace Display;
		using namespace Geometry;

		class Element
		{
			Rectangle rect;
			const Image* image;
			Color color;

			public:
			Element(const Rectangle& rect, const Color& color);
			Element(const Point& position, const Image* image, const Color& color);

			virtual ~Element();
			virtual void Update();
			virtual void Render(const Image* target, const Point& offset) const;

			const Rectangle& Area() const;
		};
	}
}

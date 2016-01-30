#pragma once
#include "../Geometry/Geometry.hpp"
#include "../Display/Display.hpp"
#include "Element.hpp"
#include <vector>

namespace Galatea
{
	namespace Platform
	{
		class Zone : public Geometry::Rectangle
		{
			std::vector<Element*> vElements;

			public:
			Zone(const Geometry::Rectangle& area);
			~Zone();

			Zone& AddOwnedElement(Element* element);

			void Update();
			void Render(const Display::Image* target, const Geometry::Rectangle* view);
		};
	}
}

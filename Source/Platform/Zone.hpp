#pragma once
#include "../Geometry/Geometry.hpp"
#include "../Display/Display.hpp"
#include "Element.hpp"
#include <vector>

namespace Galatea
{
	namespace Platform
	{
		using namespace Geometry;
		using namespace Display;

		class Zone : public Rectangle
		{
			std::vector<Element*> vElements;

			public:
			Zone(const Rectangle& area);
			~Zone();

			Zone& AddOwnedElement(Element* element);

			void Update();
			void Render(const Image* target, const Rectangle* view);
		};
	}
}

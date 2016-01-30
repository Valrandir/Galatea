#include "Zone.hpp"

namespace Galatea
{
	namespace Platform
	{
		using namespace Geometry;
		using namespace Display;

		Zone::Zone(const Rectangle& area) : Rectangle{area} {}

		Zone::~Zone()
		{
			for(auto& e : vElements)
				delete e;
		}

		Zone& Zone::AddOwnedElement(Element* element)
		{
			vElements.emplace_back(element);
			return *this;
		}

		void Zone::Update()
		{
			for(auto &e : vElements)
				e->Update();
		}

		void Zone::Render(const Image* target, const Rectangle* view)
		{
			Point offset = -view->Position();

			for(auto &e : vElements)
				if(e->Area().Intersect(*view))
					e->Render(target, offset);
		}
	}
}

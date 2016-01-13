#include "Element.hpp"

namespace Galatea
{
	namespace Platform
	{
		Element::Element(const Rectangle& rect, const Color& color) : rect{rect}, image{}, color{color}
		{
		}

		Element::Element(const Point& position, const Image* image, const Color& color) : image{image}, color{color}
		{
			rect.SetPosition(position);
			rect.SetSize({image->Width(), image->Height()});
		}

		Element::~Element()
		{
		}

		void Element::Update()
		{
		}

		void Element::Render(const Image* target, const Point& offset) const
		{
			Rectangle rect{this->rect};

			rect.Offset(offset);

			if(image)
				target->DrawImage(rect.Position(), image, color);
			else
				target->DrawRect(rect, color);
		}

		const Rectangle& Element::Area() const
		{
			return rect;
		}
	}
}

//A Shape is just a Rectangle with an owner and a list of child shapes.
#pragma once
#include "Rectangle.hpp"
#include "../Display/Renderer.hpp"
#include <vector>

namespace Engine
{
	namespace Geometry
	{
		using namespace Display;

		class Shape : public Rectangle
		{
			void* _owner{};
			bool _notified{};
			std::vector<Shape*> _shape_list;

			public:
			Shape(const Rectangle& src);
			Shape& AddShape(Shape* src);

			bool Intersect(Shape& src);
			void Notify(Shape& src);

			void MoveTo(const Point& position);

			void Render(const Renderer& renderer) const;
		};
	}
}

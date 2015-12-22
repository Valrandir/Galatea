#include "Shape.hpp"

namespace Engine
{
	namespace Geometry
	{
		Shape::Shape(const Rectangle& src) : Rectangle{src} {}

		Shape& Shape::AddShape(Shape* src)
		{
			_shape_list.push_back(src);
			return *this;
		}

		bool Shape::Intersect(Shape& src)
		{
			if(Rectangle::Intersect(src))
			{
				if(_shape_list.size() && src._shape_list.size())
				{
					bool intersected{};

					for(auto& shape : _shape_list)
					{
						for(auto& src_shape : src._shape_list)
						{
							if(shape->Intersect(*src_shape))
							{
								intersected = true;
							}
						}
					}

					return intersected;
				}
				else
				{
					Notify(src);
					src.Notify(*this);
					return true;
				}
			}

			return false;
		}

		void Shape::Notify(Shape& src)
		{
			_notified = true;

			for(auto& shape : _shape_list)
				shape->Notify(src);
		}

		void Shape::MoveTo(const Point& position)
		{
			auto offset = position - this->position;
			this->position = position;

			for(auto& shape : _shape_list)
			{
				auto newpos = shape->position + offset;
				shape->MoveTo(newpos);
			}
		}

		void Shape::Render(const Renderer& renderer) const
		{
			Color color = Color::Random();
			color.red = _notified ? 0xff : 0x0;

			color.alpha = 0x20;
			renderer.DrawRect(*this, color);

			for(auto& shape : _shape_list)
				shape->Render(renderer);
		}
	}
}

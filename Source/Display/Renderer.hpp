#pragma once
#include "Color.hpp"
#include "Image.hpp"
#include "../Geometry/Rectangle.hpp"
#include "../Geometry/Point.hpp"

namespace Galatea
{
	namespace Display
	{
		using namespace Geometry;

		class Renderer
		{
			public:
			Renderer() = default;
			Renderer(const Renderer&) = delete;
			Renderer& operator=(const Renderer&) = delete;

			virtual void Clear(Color color = Color()) const = 0;
			virtual void DrawRect(const Rectangle& rectangle, Color color) const = 0;
			virtual void DrawImage(const Point& position, const Image* image, Color color = {0xff, 0xff, 0xff}, bool horizontal_flip = false, bool vertical_flip = false) const = 0;
			virtual void DrawImage(const Point& position, Rectangle source, const Image* image, Color color = {0xff, 0xff, 0xff}, bool horizontal_flip = false, bool vertical_flip = false) const = 0;

			virtual int Width() const = 0;
			virtual int Height() const = 0;
		};
	}
}

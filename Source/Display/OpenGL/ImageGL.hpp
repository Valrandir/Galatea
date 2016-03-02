#pragma once

#include "../Image.hpp"
#include "../Color.hpp"

namespace Galatea
{
	namespace Display
	{
		class ImageGL : public virtual Image
		{
			int _width, _height;

			public:
			~ImageGL();

			void Clear(Color color = Color()) const override;
			void DrawRect(const Geometry::Rectangle& rectangle, Color color) const override;
			void DrawRect(int x, int y, int width, int height, Color color) const override;
			void DrawImage(const Geometry::Point& position, const Image* image, Color color = {0xff, 0xff, 0xff}, bool horizontal_flip = false, bool vertical_flip = false) const override;
			void DrawImage(const Geometry::Point& position, Geometry::Rectangle source, const Image* image, Color color = {0xff, 0xff, 0xff}, bool horizontal_flip = false, bool vertical_flip = false) const override;

			int Width() const override;
			int Height() const override;
		};
	}
}

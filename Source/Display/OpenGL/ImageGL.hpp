#pragma once

#include "../Image.hpp"
#include "../Color.hpp"
#include <vector>

namespace Galatea
{
	namespace Display
	{
		struct DrawItem
		{
			Geometry::Rectangle rect;
			Color color;
		};

		typedef std::vector<DrawItem> VectorDrawItem;

		class ImageGL : public virtual Image
		{
			int _width, _height;
			VectorDrawItem* _vec_drawitem;

			public:
			ImageGL(int width, int height, VectorDrawItem* vec_drawitem);
			~ImageGL();

			void Clear(Color color = Color()) const override;
			void DrawRect(const Geometry::Rectangle& rectangle, Color color) const override;
			void DrawRect(int x, int y, int width, int height, Color color) const override;
			void DrawImage(const Geometry::Point& position, const Image* image, Color color = {0xff, 0xff, 0xff}, bool horizontal_flip = false, bool vertical_flip = false) const override;
			void DrawImage(const Geometry::Point& position, Geometry::Rectangle source, const Image* image, Color color = {0xff, 0xff, 0xff}, bool horizontal_flip = false, bool vertical_flip = false) const override;

			inline int Width() const override { return _width; }
			inline int Height() const override { return _height; }
		};
	}
}

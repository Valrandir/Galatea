#include "../../Assert/Assert.hpp"
#include "ImageGL.hpp"

namespace Galatea
{
	namespace Display
	{
		using namespace Geometry;

		ImageGL::ImageGL(int width, int height, VectorDrawItem* vec_drawitem) : _width{width}, _height{height}, _vec_drawitem{vec_drawitem}
		{
		}

		ImageGL::~ImageGL()
		{
		}

		void ImageGL::Clear(Color color) const
		{
		}

		void ImageGL::DrawRect(const Rectangle& rectangle, Color color) const
		{
			if(!_vec_drawitem)
				return;

			_vec_drawitem->emplace_back(DrawItem{rectangle, color});
		}

		void ImageGL::DrawRect(int x, int y, int width, int height, Color color) const
		{
			DrawRect({Point{x, y}, Size{width, height}}, color);
		}

		void ImageGL::DrawImage(const Point& position, const Image* image, Color color, bool horizontal_flip, bool vertical_flip) const
		{
			DrawRect({position, Size{image->Width(), image->Height()}}, color);
		}

		void ImageGL::DrawImage(const Point& position, Rectangle source, const Image* image, Color color, bool horizontal_flip, bool vertical_flip) const
		{
			DrawRect({position, Size{image->Width(), image->Height()}}, color);
		}
	}
}

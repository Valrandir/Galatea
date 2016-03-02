#include "../../Assert/Assert.hpp"
#include "ImageGL.hpp"

namespace Galatea
{
	namespace Display
	{
		using namespace Geometry;

		ImageGL::~ImageGL()
		{
		}

		void ImageGL::Clear(Color color) const
		{
		}

		void ImageGL::DrawRect(const Rectangle& rectangle, Color color) const
		{
			DrawRect(rectangle.x1, rectangle.y1, rectangle.Width(), rectangle.Height(), color);
		}

		void ImageGL::DrawRect(int x, int y, int width, int height, Color color) const
		{
		}

		void ImageGL::DrawImage(const Point& position, const Image* image, Color color, bool horizontal_flip, bool vertical_flip) const
		{
		}

		void ImageGL::DrawImage(const Point& position, Rectangle source, const Image* image, Color color, bool horizontal_flip, bool vertical_flip) const
		{
		}

		int ImageGL::Width() const { return _width; }
		int ImageGL::Height() const { return _height; }
	}
}

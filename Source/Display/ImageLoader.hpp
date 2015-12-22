#include "Color.hpp"

namespace Galatea
{
	namespace Display
	{
		struct ImageLoader
		{
			virtual Image* CreateImage(int width, int height) const = 0;
			virtual Image* CreateImage(const char* file) const = 0;
		};
	}
}

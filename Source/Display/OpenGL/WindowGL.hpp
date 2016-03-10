#pragma once
#include "../../Types.hpp"
#include "../Window.hpp"
#include "../WindowStyle.hpp"
#include "ImageGL.hpp"

namespace Galatea
{
	namespace Display
	{
		class WindowGL : public Window, public ImageGL
		{
			public:
			static WindowGL* Create(CStr title, int width, int height, WindowStyle style);
			virtual ~WindowGL(){}
		};
	}
}

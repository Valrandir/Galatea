#pragma once
#include "Color.hpp"
#include "Image.hpp"
#include "Sprite.hpp"
#include "Window.hpp"
#include "WindowStyle.hpp"

namespace Galatea
{
	namespace Display
	{
		Window* CreateWindow(CStr title, int width, int height);
		Window* CreateWindow(CStr title, int width, int height, WindowStyle style);
	}
}

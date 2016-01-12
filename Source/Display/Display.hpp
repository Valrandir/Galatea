#pragma once
#include "Color.hpp"
#include "Image.hpp"
#include "Sprite.hpp"
#include "Window.hpp"

namespace Galatea
{
	namespace Display
	{
		Window* CreateWindow(const char* title, int width, int height);
	}
}

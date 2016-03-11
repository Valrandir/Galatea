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
		enum class RendererImpl
		{
			SDL,
			OpenGL
		};

		Window* CreateWindow(RendererImpl renderer, CStr title, int width, int height, WindowStyle style);
		Window* CreateWindow(RendererImpl renderer, CStr title, int width, int height);
	}
}

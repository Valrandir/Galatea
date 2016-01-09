#pragma once
#include "Window.hpp"
#include "Image.hpp"

namespace Galatea
{
	namespace Display
	{
		class Renderer
		{
			public:
			Renderer() = default;
			Renderer(const Renderer&) = delete;
			Renderer& operator=(const Renderer&) = delete;

			virtual Window* CreateWindow(const char* title, int width, int height) const = 0;
			virtual Image* CreateImage(int width, int height) const = 0;
			virtual Image* CreateImage(const char* file) const = 0;

			static Renderer* Create();
		};
	}
}

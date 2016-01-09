#pragma once
#include "../Renderer.hpp"
#include <SDL.h>

namespace Galatea
{
	namespace Display
	{
		class RendererSDL : public Renderer
		{
			SDL_Window* _window{};
			SDL_Renderer* _renderer{};

			public:
			RendererSDL();
			~RendererSDL();
			void Destroy();
			Window* CreateWindow(const char* title, int width, int height) const override;
			Image* CreateImage(int width, int height) const override;
			Image* CreateImage(const char* file) const override;
		};
	}
}

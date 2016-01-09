#include "RendererSDL.hpp"
#include "WindowSDL.hpp"
#include "ImageSDL.hpp"

namespace Galatea
{
	namespace Display
	{
		RendererSDL::RendererSDL()
		{
			_window = SDL_CreateWindow("GalateaCoreWindowSDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);

			if(_window == nullptr)
				return;

			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(_renderer == nullptr)
			{
				Destroy();
				return;
			}
		}

		RendererSDL::~RendererSDL()
		{
			Destroy();
		}

		void RendererSDL::Destroy()
		{
			if(_renderer)
			{
				SDL_DestroyRenderer(_renderer);
				_renderer = nullptr;
			}

			if(_window)
			{
				SDL_DestroyWindow(_window);
				_window = nullptr;
			}
		}

		Window* RendererSDL::CreateWindow(const char* title, int width, int height) const
		{
			//Does not support multiple windows, this will only create another access point to the main window
			auto window = new WindowSDL(title, width, height, _renderer);
			SDL_ShowWindow(_window);
			return window;
		}

		Image* RendererSDL::CreateImage(int width, int height) const
		{
			return new ImageSDL(width, height, _renderer);
		}

		Image* RendererSDL::CreateImage(const char* file) const
		{
			return new ImageSDL(file, _renderer);
		}
	}
}

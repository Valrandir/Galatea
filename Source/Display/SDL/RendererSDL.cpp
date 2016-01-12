#include "../../Assert/Assert.hpp"
#include "RendererSDL.hpp"
#include "WindowSDL.hpp"
#include "ImageSDL.hpp"

namespace Galatea
{
	namespace Display
	{
		RendererSDL::RendererSDL()
		{
			ASSERT(_window = SDL_CreateWindow("GalateaCoreWindowSDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL));
			ASSERT(_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
		}

		RendererSDL::~RendererSDL()
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
			SDL_Window* window;
			ASSERT(window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL));

			SDL_Renderer* renderer;
			ASSERT(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

			auto win = new WindowSDL(title, width, height, renderer, window);

auto z = (RendererSDL*)this;
z->_renderer = renderer;
z->_window = window;

			return win;
		}

		Image* RendererSDL::CreateImage(int width, int height) const
		{
			return new ImageSDL(width, height, _renderer, true);
		}

		Image* RendererSDL::CreateImage(const char* file) const
		{
			return new ImageSDL(file, _renderer);
		}
	}
}

#include "../../Assert/Assert.hpp"
#include "WindowSDL.hpp"
#include "ImageSDL.hpp"
#include "InputSDL.hpp"

namespace Galatea
{
	namespace Display
	{
		WindowSDL::WindowSDL(const char* title, int width, int height, SDL_Window* window, SDL_Renderer* renderer) :
			ImageSDL{width, height, renderer},
			_window{window},
			_renderer{renderer},
			_is_destroyed{}
		{
		}

		WindowSDL* WindowSDL::Create(const char* title, int width, int height)
		{
			SDL_Window* window;
			ASSERT(window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL));

			SDL_Renderer* renderer;
			ASSERT(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

			return new WindowSDL(title, width, height, window, renderer);
		}

		WindowSDL::~WindowSDL()
		{
			Destroy();
		}

		void WindowSDL::Destroy()
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

			_is_destroyed = true;
		}

		Image* WindowSDL::CreateImage(int width, int height) const
		{
			return new ImageSDL(width, height, _renderer, true);
		}

		Image* WindowSDL::CreateImage(const char* file) const
		{
			return new ImageSDL(file, _renderer);
		}

		void WindowSDL::BeginDraw(bool clear)
		{
			if(clear)
				Clear();
		}

		void WindowSDL::EndDraw()
		{
			SDL_RenderPresent(_renderer);
		}

		bool WindowSDL::Update()
		{
			if(_is_destroyed)
				return false;

			SDL_Event e;
			while(SDL_PollEvent(&e))
			{
				if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
					_is_destroyed = true;
				else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
					OnKey(ToKeyEvent(e.type, e.key.keysym));
			}

			return !_is_destroyed;
		}

		void WindowSDL::Close()
		{
			Destroy();
		}
	}
}

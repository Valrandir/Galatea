#include "WindowSDL.hpp"
#include "ImageSDL.hpp"
#include "InputSDL.hpp"

namespace Galatea
{
	namespace Display
	{
		WindowSDL::WindowSDL(const char* title, int width, int height, SDL_Renderer* renderer) : ImageSDL{width, height, renderer}, _renderer{renderer}, _is_destroyed{}
		{
		}

		WindowSDL::~WindowSDL()
		{
			_is_destroyed = true;
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
			_is_destroyed = true;
		}
	}
}

#include "../../Assert/Assert.hpp"
#include "../Display.hpp"
#include "WindowSDL.hpp"
#include "ImageSDL.hpp"
#include "InputSDL.hpp"

namespace Galatea
{
	namespace Display
	{
		WindowSDL::WindowSDL(CStr title, int width, int height, SDL_Window* window, SDL_Renderer* renderer) :
			ImageSDL{width, height, renderer, false},
			_window{window},
			_renderer{renderer},
			_is_destroyed{}
		{
		}

		WindowSDL* WindowSDL::Create(CStr title, int width, int height, WindowStyle style)
		{
			SDL_Window* window;
			Uint32 flags = style & WindowStyle::Borderless ? SDL_WINDOW_BORDERLESS : 0;

			if(!SDL_WasInit(SDL_INIT_VIDEO))
				SDL_Init(SDL_INIT_VIDEO);

			if(!width || !height)
			{
				SDL_DisplayMode sdm;
				ASSERT(SDL_GetDesktopDisplayMode(0, &sdm) == 0);
				width = sdm.w;
				height = sdm.h;
			}

			auto char_title = String::WideToByte(title);
			ASSERT(window = SDL_CreateWindow(char_title.get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_OPENGL));

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
			return new ImageSDL(width, height, _renderer);
		}

		Image* WindowSDL::CreateImage(const char* file) const
		{
			auto src = new ImageSDL(file, _renderer);
			auto img = new ImageSDL(src->Width(), src->Height(), _renderer); //Create with SDL_TEXTUREACCESS_TARGET to make it writable

			img->DrawImage({}, src);
			delete src;

			return img;
		}

		Image* WindowSDL::CreateImage(const void* memory, Int size) const
		{
			auto src = new ImageSDL(memory, size, _renderer);
			auto img = new ImageSDL(src->Width(), src->Height(), _renderer); //Create with SDL_TEXTUREACCESS_TARGET to make it writable

			img->DrawImage({}, src);
			delete src;

			return img;
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
				else if(e.type == SDL_MOUSEBUTTONUP)
				{
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT: OnMouseUp(1); break;
						case SDL_BUTTON_RIGHT: OnMouseUp(2); break;
						case SDL_BUTTON_MIDDLE: OnMouseUp(3); break;
					}
				}
				else if(e.type == SDL_MOUSEBUTTONDOWN)
				{
					switch(e.button.button)
					{
						case SDL_BUTTON_LEFT: OnMouseDown(1); break;
						case SDL_BUTTON_RIGHT: OnMouseDown(2); break;
						case SDL_BUTTON_MIDDLE: OnMouseDown(3); break;
					}
				}
				else if(e.type == SDL_MOUSEMOTION)
				{
					OnMouseMove(e.motion.x, e.motion.y);
				}
			}

			return !_is_destroyed;
		}

		void WindowSDL::Close()
		{
			Destroy();
		}

		void WindowSDL::MousePosition(int& x, int& y) const
		{
			SDL_GetMouseState(&x, &y);
		}
	}
}

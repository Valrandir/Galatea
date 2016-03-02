#pragma once
#include "../Window.hpp"
#include "ImageSDL.hpp"
#include <SDL.h>

namespace Galatea
{
	namespace Display
	{
		class WindowSDL : public Window, public ImageSDL
		{
			SDL_Window* _window;
			SDL_Renderer* _renderer;
			bool _is_destroyed;

			WindowSDL(const char* title, int width, int height, SDL_Window* window, SDL_Renderer* renderer);

			public:
			static WindowSDL* Create(const char* title, int width, int height, WindowStyle style);
			~WindowSDL();
			void Destroy();

			Image* CreateImage(int width, int height) const override;
			Image* CreateImage(const char* file) const override;
			Image* CreateImage(const void* memory, Int size) const override;

			void BeginDraw(bool clear = true) override;
			void EndDraw() override;
			bool Update() override;
			void Close() override;
			void MousePosition(int& x, int& y) const override;
		};
	}
}

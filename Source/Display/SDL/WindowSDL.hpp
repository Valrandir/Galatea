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
			SDL_Renderer* _renderer{};
			bool _is_destroyed;

			public:
			WindowSDL(const char* title, int width, int height, SDL_Renderer* renderer);
			~WindowSDL();

			void BeginDraw(bool clear = true) override;
			void EndDraw() override;
			bool Update() override;
			void Close() override;
		};
	}
}

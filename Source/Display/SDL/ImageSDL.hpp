#pragma once

#include "../Image.hpp"
#include <SDL.h>

namespace Galatea
{
	namespace Display
	{
		class ImageSDL : public Image
		{
			int _width, _height;
			SDL_Texture* _texture;

			public:
			ImageSDL(const char* file, SDL_Renderer* renderer);
			ImageSDL(const ImageSDL&) = delete;
			ImageSDL& operator=(const ImageSDL&) = delete;
			~ImageSDL();

			SDL_Texture* Texture() const;
			int Width() const;
			int Height() const;
		};
	}
}

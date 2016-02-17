#pragma once

#include "../Image.hpp"
#include "../Color.hpp"
#include <SDL.h>

namespace Galatea
{
	namespace Display
	{
		class ImageSDL : public virtual Image
		{
			int _width, _height;
			SDL_Texture* _texture;
			SDL_Renderer* _renderer;
			bool _use_texture;

			public:
			ImageSDL(int width, int height, SDL_Renderer* renderer, bool use_texture = true);
			ImageSDL(const char* file, SDL_Renderer* renderer);
			ImageSDL(const void* memory, Int size, SDL_Renderer* renderer);
			~ImageSDL();

			SDL_Texture* Texture() const;

			void Clear(Color color = Color()) const override;
			void DrawRect(const Geometry::Rectangle& rectangle, Color color) const override;
			void DrawRect(int x, int y, int width, int height, Color color) const override;
			void DrawImage(const Geometry::Point& position, const Image* image, Color color = {0xff, 0xff, 0xff}, bool horizontal_flip = false, bool vertical_flip = false) const override;
			void DrawImage(const Geometry::Point& position, Geometry::Rectangle source, const Image* image, Color color = {0xff, 0xff, 0xff}, bool horizontal_flip = false, bool vertical_flip = false) const override;

			int Width() const override;
			int Height() const override;
		};
	}
}

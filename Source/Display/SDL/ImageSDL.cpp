#include "../../Assert/Assert.hpp"
#include "ImageSDL.hpp"
#include <SDL_image.h>

namespace Galatea
{
	namespace Display
	{
		ImageSDL::ImageSDL(int width, int height, SDL_Renderer* renderer, bool use_texture) : _width{width}, _height{height}, _renderer{renderer}, _use_texture{use_texture}
		{
			ASSERT(_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height));
		}

		ImageSDL::ImageSDL(const char* file, SDL_Renderer* renderer) : _renderer{renderer}, _use_texture{true}
		{
			SDL_Surface* surface;
			ASSERT(surface = IMG_Load(file));

			_width = surface->w;
			_height = surface->h;
			ASSERT(_texture = SDL_CreateTextureFromSurface(renderer, surface));

			SDL_FreeSurface(surface);
		}

		ImageSDL::~ImageSDL()
		{
			_width = 0;
			_height = 0;

			if(_texture)
			{
				SDL_DestroyTexture(_texture);
				_texture = nullptr;
			}
		}

		SDL_Texture* ImageSDL::Texture() const { return _texture; }

		void ImageSDL::Clear(Color color) const
		{
			SDL_SetRenderDrawColor(_renderer, color.red, color.green, color.blue, color.alpha);
			SDL_RenderClear(_renderer);
		}

		void ImageSDL::DrawRect(const Rectangle& rectangle, Color color) const
		{
			SDL_SetRenderDrawColor(_renderer, color.red, color.green, color.blue, color.alpha);
			SDL_SetRenderDrawBlendMode(_renderer, color.alpha == 0xff ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);

			if(_use_texture)
				SDL_SetRenderTarget(_renderer, _texture);

			SDL_Rect rect{rectangle.x1, rectangle.y1, rectangle.Width(), rectangle.Height()};
			SDL_RenderFillRect(_renderer, &rect);

			if(_use_texture)
				SDL_SetRenderTarget(_renderer, nullptr);
		}

		void ImageSDL::DrawImage(const Point& position, const Image* image, Color color, bool horizontal_flip, bool vertical_flip) const
		{
			const ImageSDL* image_sdl = dynamic_cast<const ImageSDL*>(image);
			SDL_Texture* texture = image_sdl->Texture();

			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture, color.alpha);
			SDL_SetTextureColorMod(texture, color.red, color.green, color.blue);

			SDL_Rect rect{position.x, position.y, image_sdl->Width(), image_sdl->Height()};

			SDL_RendererFlip flip = SDL_FLIP_NONE;
			if(horizontal_flip) flip = SDL_RendererFlip(flip | SDL_FLIP_HORIZONTAL);
			if(vertical_flip) flip = SDL_RendererFlip(flip | SDL_FLIP_VERTICAL);

			if(_use_texture)
				SDL_SetRenderTarget(_renderer, _texture);

			if(flip)
				SDL_RenderCopyEx(_renderer, texture, nullptr, &rect, 0.0, nullptr, flip);
			else
				SDL_RenderCopy(_renderer, texture, nullptr, &rect);

			if(_use_texture)
				SDL_SetRenderTarget(_renderer, nullptr);
		}

		void ImageSDL::DrawImage(const Point& position, Rectangle source, const Image* image, Color color, bool horizontal_flip, bool vertical_flip) const
		{
			const ImageSDL* image_sdl = dynamic_cast<const ImageSDL*>(image);
			SDL_Texture* texture = image_sdl->Texture();

			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
			SDL_SetTextureAlphaMod(texture, color.alpha);
			SDL_SetTextureColorMod(texture, color.red, color.green, color.blue);

			SDL_Rect sdl_target{position.x, position.y, source.Width(), source.Height()};
			SDL_Rect sdl_source{source.x1, source.y1, source.Width(), source.Height()};

			SDL_RendererFlip flip = SDL_FLIP_NONE;
			if(horizontal_flip) flip = SDL_RendererFlip(flip | SDL_FLIP_HORIZONTAL);
			if(vertical_flip) flip = SDL_RendererFlip(flip | SDL_FLIP_VERTICAL);

			if(_use_texture)
				SDL_SetRenderTarget(_renderer, _texture);

			if(flip)
				SDL_RenderCopyEx(_renderer, texture, &sdl_source, &sdl_target, 0.0, nullptr, flip);
			else
				SDL_RenderCopy(_renderer, texture, &sdl_source, &sdl_target);

			if(_use_texture)
				SDL_SetRenderTarget(_renderer, nullptr);
		}

		int ImageSDL::Width() const { return _width; }
		int ImageSDL::Height() const { return _height; }
	}
}

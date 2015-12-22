#include "WindowSDL.hpp"
#include "ImageSDL.hpp"
#include "InputSDL.hpp"

namespace Galatea
{
	namespace Display
	{
		WindowSDL::WindowSDL(const char* title, int width, int height) : _width{width}, _height{height}
		{
			_is_destroyed = true;

			_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

			if(_window == nullptr)
				return;

			_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(_renderer == nullptr)
			{
				Destroy();
				return;
			}

			_is_destroyed = false;
		}

		WindowSDL::~WindowSDL()
		{
			Destroy();
		}

		void WindowSDL::BeginDraw(bool clear)
		{
			if(clear)
				Clear();
		}

		void WindowSDL::Clear(Color color) const
		{
			SDL_SetRenderDrawColor(_renderer, color.red, color.green, color.blue, color.alpha);
			SDL_RenderClear(_renderer);
		}

		void WindowSDL::DrawRect(const Rectangle& rectangle, Color color) const
		{
			SDL_SetRenderDrawColor(_renderer, color.red, color.green, color.blue, color.alpha);
			SDL_SetRenderDrawBlendMode(_renderer, color.alpha == 0xff ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
			SDL_Rect rect{rectangle.position.x, rectangle.position.y, rectangle.size.x, rectangle.size.y};
			SDL_RenderFillRect(_renderer, &rect);
		}

		void WindowSDL::DrawImage(const Point& position, const Image* image, Color color, bool horizontal_flip, bool vertical_flip) const
		{
			const ImageSDL* image_sdl = dynamic_cast<const ImageSDL*>(image);
			SDL_Texture* texture = image_sdl->Texture();
			SDL_SetTextureColorMod(texture, color.red, color.green, color.blue);
			SDL_Rect rect{position.x, position.y, image_sdl->Width(), image_sdl->Height()};

			SDL_RendererFlip flip = SDL_FLIP_NONE;
			if(horizontal_flip) flip = SDL_RendererFlip(flip | SDL_FLIP_HORIZONTAL);
			if(vertical_flip) flip = SDL_RendererFlip(flip | SDL_FLIP_VERTICAL);

			if(flip)
				SDL_RenderCopyEx(_renderer, texture, nullptr, &rect, 0.0, nullptr, flip);
			else
				SDL_RenderCopy(_renderer, texture, nullptr, &rect);
		}

		void WindowSDL::DrawImage(const Point& position, Rectangle source, const Image* image, Color color, bool horizontal_flip, bool vertical_flip) const
		{
			const ImageSDL* image_sdl = dynamic_cast<const ImageSDL*>(image);
			SDL_Texture* texture = image_sdl->Texture();
			SDL_SetTextureColorMod(texture, color.red, color.green, color.blue);
			SDL_Rect sdl_target{position.x, position.y, source.size.x, source.size.y};
			SDL_Rect sdl_source{source.position.x, source.position.y, source.size.x, source.size.y};

			SDL_RendererFlip flip = SDL_FLIP_NONE;
			if(horizontal_flip) flip = SDL_RendererFlip(flip | SDL_FLIP_HORIZONTAL);
			if(vertical_flip) flip = SDL_RendererFlip(flip | SDL_FLIP_VERTICAL);

			if(flip)
				SDL_RenderCopyEx(_renderer, texture, &sdl_source, &sdl_target, 0.0, nullptr, flip);
			else
				SDL_RenderCopy(_renderer, texture, &sdl_source, &sdl_target);
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

		Image* WindowSDL::CreateImage(int width, int height) const
		{
			return new ImageSDL(width, height, _renderer);
		}

		Image* WindowSDL::CreateImage(const char* file) const
		{
			return new ImageSDL(file, _renderer);
		}

		int WindowSDL::Width() const { return _width; }
		int WindowSDL::Height() const { return _height; }

		void WindowSDL::Destroy()
		{
			_width = 0;
			_height = 0;
			_is_destroyed = true;

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
	}
}

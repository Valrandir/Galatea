#pragma once
#include "../Timing/Rate.hpp"
#include "Image.hpp"
#include "Renderer.hpp"

namespace Galatea
{
	namespace Display
	{
		using namespace Timing;

		class Sprite
		{
			Point _size;
			int _frame_count;
			int _frame_index;
			const Image* _image;
			Rate _rate;
			bool _horizontal_flip = false;
			bool _vertical_flip = false;

			public:
			Sprite(int frame_count, const Image* image, int updates_per_second);
			Sprite(const Sprite&) = delete;
			Sprite& operator=(const Sprite&) = delete;
			~Sprite();

			void SetFlip(bool horizontal_flip, bool vertical_flip);
			void Draw(const Point& position, const Renderer* renderer);

			Point Size() const;
			int FrameCount() const;
			int FrameIndex() const;
		};
	}
}

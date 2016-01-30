#pragma once
#include "../Timing/Rate.hpp"
#include "Image.hpp"

namespace Galatea
{
	namespace Display
	{
		class Sprite
		{
			Geometry::Point _size;
			int _frame_count;
			int _frame_index;
			const Image* _image;
			Timing::Rate _rate;
			bool _horizontal_flip = false;
			bool _vertical_flip = false;

			public:
			Sprite(int frame_count, const Image* source, int updates_per_second);
			Sprite(const Sprite&) = delete;
			Sprite& operator=(const Sprite&) = delete;
			~Sprite();

			void SetFlip(bool horizontal_flip, bool vertical_flip);
			void Update();
			void Draw(const Geometry::Point& position, const Image* target) const;

			Geometry::Point Size() const;
			int FrameCount() const;
			int FrameIndex() const;
		};
	}
}

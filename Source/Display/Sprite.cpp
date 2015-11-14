#include "Sprite.hpp"

namespace Galatea
{
	namespace Display
	{
		Sprite::Sprite(int frame_count, const Image* image, int updates_per_second) :
			_size{image->Width() / frame_count, image->Height()},
			_rate(updates_per_second),
			_image{image},
			_frame_count{frame_count},
			_frame_index{}
		{}

		Sprite::~Sprite()
		{
			if(_image)
			{
				delete _image;
				_image = nullptr;
			}
		}

		void Sprite::SetFlip(bool horizontal_flip, bool vertical_flip)
		{
			_horizontal_flip = horizontal_flip;
			_vertical_flip = vertical_flip;
		}

		void Sprite::Draw(const Point& position, const Renderer* renderer)
		{
			renderer->DrawImage(position, {{_frame_index * _size.x, 0}, {_size.x, _size.y}}, _image, Color(255, 255, 255), _horizontal_flip, _vertical_flip);

			_frame_index += _rate.Update();
			if(_frame_index >= _frame_count)
				_frame_index %= _frame_count;
		}

		Point Sprite::Size() const { return _size; }
		int Sprite::FrameCount() const { return _frame_count; }
		int Sprite::FrameIndex() const { return _frame_index; }
	}
}

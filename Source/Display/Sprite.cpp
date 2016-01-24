#include "Sprite.hpp"

namespace Galatea
{
	namespace Display
	{
		Sprite::Sprite(int frame_count, const Image* source, int updates_per_second) :
			_size{source->Width() / frame_count, source->Height()},
			_rate(updates_per_second),
			_image{source},
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

		void Sprite::Update()
		{
			_frame_index += _rate.Update();

			if(_frame_index >= _frame_count)
				_frame_index %= _frame_count;
		}

		void Sprite::Draw(const Point& position, const Image* target) const
		{
			target->DrawImage(position, {Point{_frame_index * _size.x, 0}, Geometry::Size{_size.x, _size.y}}, _image, Color(255, 255, 255), _horizontal_flip, _vertical_flip);
		}

		Point Sprite::Size() const { return _size; }
		int Sprite::FrameCount() const { return _frame_count; }
		int Sprite::FrameIndex() const { return _frame_index; }
	}
}

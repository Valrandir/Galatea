#include "../Galatea.hpp"
#define DeletePtr(ptr)if(ptr) { delete ptr; ptr = nullptr; }

using namespace Galatea;
using namespace Display;
using namespace Geometry;
using namespace Platform;

extern void GetPngSpriteData(const UInt8*& png_sample_data, Int& size);

namespace
{
	Window* _window;
	Sprite* _sprite;

	const int _screen_width = 0x100;
	const int _screen_height = 0x100;

	bool Init()
	{
		_window = CreateWindow("Sprite Test", _screen_width, _screen_height);

		const UInt8* png_sample_data;
		Int png_sample_size;
		GetPngSpriteData(png_sample_data, png_sample_size);
		Image* img = _window->CreateImage(png_sample_data, png_sample_size);

		_sprite = new Sprite(4, img, 10);

		return true;
	}

	bool Update()
	{
		_sprite->Update();
		return true;
	}

	bool Render()
	{
		_window->BeginDraw();

		Point position;

		//Top
		position = Point{_screen_width / 2, _screen_height / 2 - _sprite->Size().y * 2} -_sprite->Size() / 2;
		_sprite->SetFlip(false, false);
		_sprite->Draw(position, _window);

		//Right
		position += _sprite->Size() * 2;
		_sprite->SetFlip(true, false);
		_sprite->Draw(position, _window);

		//Bottom
		position.x -= _sprite->Size().x * 2;
		position.y += _sprite->Size().y * 2;
		_sprite->SetFlip(false, true);
		_sprite->Draw(position, _window);

		//Left
		position -= _sprite->Size() * 2;
		_sprite->SetFlip(true, true);
		_sprite->Draw(position, _window);

		_window->EndDraw();

		return _window->Update();
	}

	void Destroy()
	{
		DeletePtr(_sprite);
		DeletePtr(_window);
	}
}

Bool SpriteTest()
{
	if(!Init())
		return false;

	while(Update() && Render());
	Destroy();

	return true;
}

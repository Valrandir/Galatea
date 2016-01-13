#include "../Galatea.hpp"
#define DeletePtr(ptr)if(ptr) { delete ptr; ptr = nullptr; }

using namespace Galatea;
using namespace Display;
using namespace Platform;

extern String CreatePngTestFile();
extern void DestroyPngTestFile();

void Init();
bool Update();
bool Render();
void Destroy();
void OnKey(KeyEvent ke, void* user_data);

const int _screen_width = 800;
const int _screen_height = 600;
const int _zone_width = 8192;
const int _zone_height = 8192;
const double _camera_impulse_force = 0.5;

Window* _window;
Image* _img_bubble;
Geometry::Point _input_direction;
Zone* _zone;
Camera* _camera;

Bool ZoneTest()
{
	Init();
	while(Update() && Render());
	Destroy();

	return true;
}

void Init()
{
	_window = CreateWindow("Zone Test", _screen_width, _screen_height);
	_window->OnKeyEvent() = OnKey;

	CreatePngTestFile();
	_img_bubble = _window->CreateImage("png_test.png");
	DestroyPngTestFile();

	_zone = new Zone({Point{}, Size{_zone_width, _zone_height}});
	_zone->AddOwnedElement(new Element{{Center{_zone_width / 2, _zone_height / 2}, Size{64, 64}}, Color::Red});

	{
		const int block_size = 32;
		auto max = ((_zone_width / block_size) * (_zone_height / block_size)) / 8;
		int mx = _zone_width - block_size;
		int my = _zone_height - block_size;
		for(int i{}; i < max; ++i)
		{
			auto x = Math::Random(0, mx);
			auto y = Math::Random(0, my);
			auto r = (UInt8)Math::Random(0, 0xff);
			auto g = (UInt8)Math::Random(0, 0xff);
			auto b = (UInt8)Math::Random(0, 0xff);
			auto a = (UInt8)Math::Random(0, 0xff);
			_zone->AddOwnedElement(new Element{Point{x, y}, _img_bubble, Color{r, g, b, a}});
		}
	}

	_camera = new Camera();
	_camera->Rectangle::SetPosition(_zone->Center() - Point{_screen_width / 2, _screen_height / 2});
	_camera->Rectangle::SetSize({_screen_width, _screen_height});
	_camera->Motion::SetPosition(_camera->Rectangle::Position().ToVector());
}

bool Update()
{
	if(_input_direction.x || _input_direction.y)
		_camera->Impulse(_input_direction.ToVector(), _camera_impulse_force);

	_camera->Update();

	_zone->Update();
	return true;
}

bool Render()
{
	_window->BeginDraw();
	_zone->Render(_window, _camera);
	_window->EndDraw();

	return _window->Update();
}

void Destroy()
{
	DeletePtr(_camera);
	DeletePtr(_zone);
	DeletePtr(_img_bubble);
	DeletePtr(_window);
}

void OnKey(KeyEvent ke, void* user_data)
{
	if(ke.up_or_down == KeyDirection::Up)
	{
		_input_direction.x = 0;
		_input_direction.y = 0;
		return;
	}

	switch(ke.key)
	{
		case Keys::KeyRight: _input_direction.x = 1; break;
		case Keys::KeyDown: _input_direction.y = 1; break;
		case Keys::KeyLeft: _input_direction.x = -1; break;
		case Keys::KeyUp: _input_direction.y = -1; break;
	}
}

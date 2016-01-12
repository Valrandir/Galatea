#include "../Galatea.hpp"
using namespace Galatea;

extern String CreatePngTestFile();
extern void DestroyPngTestFile();

Bool DisplayTest()
{
	const int width{320}, height{240};
	auto wnd = Display::CreateWindow("Test Window", width, height);

	if(!wnd)
		return false;

	Display::Image* blue = wnd->CreateImage(width, height);
	for(int it{20}; it <= 120; it += 10)
		blue->DrawRect({{it, it},{width - it - it, height - it - it}}, {0, 0, static_cast<UInt8>(it)});

	auto png_file = CreatePngTestFile();
	Display::Image* png = wnd->CreateImage("png_test.png");
	DestroyPngTestFile();

	while(wnd->Update())
	{
		wnd->BeginDraw();
		wnd->DrawImage({}, blue);
		wnd->DrawImage({}, png, Display::Color{0xff, 0x80, 0x80, 0xA0});
		wnd->EndDraw();
		Timing::Sleep(1u);
	}

	delete png;
	delete blue;
	delete wnd;

	return true;
}

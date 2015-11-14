#include "../Galatea.hpp"
using namespace Galatea;

Bool DisplayTest()
{
	const int width{320}, height{240};
	auto wnd = Display::Window::Create("Test Window", width, height);

	if(!wnd)
		return false;

	while(wnd->Update())
	{
		wnd->BeginDraw();
		wnd->Clear({});
		for(int it{20}; it <= 120; it += 10)
			wnd->DrawRect({{it, it}, {width - it -it, height - it - it}}, {0, 0, static_cast<UInt8>(it)});
		wnd->EndDraw();
		Galatea::Timing::Sleep(1u);
	}

	return true;
}

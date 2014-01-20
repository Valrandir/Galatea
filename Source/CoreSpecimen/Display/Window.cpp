#include "../Core.hpp"

using namespace Core;
using namespace Display;

namespace DisplayTestNamespace
{
	Bool OpenWindow()
	{
		Bool result = true;

		Window* wnd = CreateWindow();
		wnd->Show();

		while(wnd->Update())
			Core::Time::Sleep(1);

		wnd->Close();
		DeletePtr(wnd);

		return result;
	}
}

Bool DisplayTest()
{
	Bool result = true;
	using namespace DisplayTestNamespace;

	CHECK OpenWindow();

	return result;
}

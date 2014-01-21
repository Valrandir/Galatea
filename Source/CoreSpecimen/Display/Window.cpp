#include "../Core.hpp"

using namespace Core;
using namespace Display;

namespace DisplayTestNamespace
{
	void OnKeydown(UInt32 key_code, VoidPtr param)
	{
		Bool result = (int)param == 55;
	}

	Bool OpenWindow()
	{
		Bool result = true;

		Window* wnd = CreateWindow();

		wnd->SetOnKeydownCallback(OnKeydown, (void*)55);
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

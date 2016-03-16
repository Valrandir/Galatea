#pragma once
#include "../../Common/Win32/WindowBase.hpp"
#include "../WindowGL.hpp"

namespace Galatea
{
	namespace Display
	{
		class WindowWGL : public WindowGL, private Common::WindowBase
		{
			bool _is_destroyed;
			HDC _hdc;
			HGLRC _gl_context;

			void InitOpenGL();
			void UpdateStyle(WindowStyle style);

			public:
			WindowWGL(CStr title, int width, int height, WindowStyle style);
			~WindowWGL();

			LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam) override;

			void BeginDraw(bool clear = true) override;
			void EndDraw() override;
			bool Update() override;
			void Close() override;
			void MousePosition(int& x, int& y) const override;
		};
	}
}

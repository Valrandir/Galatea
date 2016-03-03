#pragma once
#include "../Common/Win32/WindowBase.hpp"
#include "../Window.hpp"
#include "ImageGL.hpp"
#include "GLExt.hpp"

namespace Galatea
{
	namespace Display
	{
		class WindowGL : public Window, public ImageGL, private Common::WindowBase
		{
			bool _is_destroyed;
			const GLExt* _glext;
			HDC _hdc;
			HGLRC _gl_context;

			void UpdateStyle(WindowStyle style);
			void InitOpenGL();

			WindowGL(CStr title, int width, int height, WindowStyle style);

			public:
			static WindowGL* Create(CStr title, int width, int height, WindowStyle style);
			~WindowGL();

			Image* CreateImage(int width, int height) const override;
			Image* CreateImage(const char* file) const override;
			Image* CreateImage(const void* memory, Int size) const override;

			void BeginDraw(bool clear = true) override;
			void EndDraw() override;
			bool Update() override;
			void Close() override;
			void MousePosition(int& x, int& y) const override;
		};
	}
}

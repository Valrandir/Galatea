#include "../../Assert/Assert.hpp"
#include "../Display.hpp"
#include "WindowGL.hpp"
#include "ImageGL.hpp"
#include "InputGL.hpp"

namespace Galatea
{
	namespace Display
	{

		void WindowGL::UpdateStyle(WindowStyle style)
		{
			DWORD ws{};

			if(style & WindowStyle::Borderless)
				ws = WS_POPUP;
			else
			{
				if(style & WindowStyle::Caption)
					ws |= WS_CAPTION;

				if(style & WindowStyle::SysMenu)
					ws |= WS_SYSMENU;

				if(style & WindowStyle::MinimizeBox)
					ws |= WS_MINIMIZEBOX;

				if(style & WindowStyle::MaximizeBox)
					ws |= WS_MAXIMIZEBOX;
			}

			SetStyle(ws);
		}

		void WindowGL::InitOpenGL()
		{
			_hdc = GetDC(_hwnd);

			int pf_attrib[] =
			{
				WGL_DRAW_TO_WINDOW_ARB, 1,
				WGL_DOUBLE_BUFFER_ARB, 1,
				WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
				WGL_COLOR_BITS_ARB, 32,
				WGL_DEPTH_BITS_ARB, 24,
				WGL_STENCIL_BITS_ARB, 8,
				0
			};

			int pixel_format;
			UINT num_formats;
			_glext->wglChoosePixelFormatARB(_hdc, pf_attrib, NULL, 1u, &pixel_format, &num_formats);
			SetPixelFormat(_hdc, pixel_format, NULL);

			int c_attrib = 0;
			_gl_context = _glext->wglCreateContextAttribsARB(_hdc, NULL, &c_attrib);
			wglMakeCurrent(_hdc, _gl_context);

			SetWindowTextA(_hwnd, (char*)glGetString(GL_VERSION));
		}

		WindowGL::WindowGL(CStr title, int width, int height, WindowStyle style) : WindowBase{title, width, height}
		{
			UpdateStyle(style);
			_glext = GLExt::Create();
			InitOpenGL();
			Show();
		}

		WindowGL* WindowGL::Create(CStr title, int width, int height, WindowStyle style)
		{
			return new WindowGL(title, width, height, style);
		}

		WindowGL::~WindowGL()
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(_gl_context);
			ReleaseDC(_hwnd, _hdc);
			DestroyWindow(_hwnd);
		}

		Image* WindowGL::CreateImage(int width, int height) const
		{
			return new ImageGL();
		}

		Image* WindowGL::CreateImage(const char* file) const
		{
			return new ImageGL();
		}

		Image* WindowGL::CreateImage(const void* memory, Int size) const
		{
			return new ImageGL();
		}

		void WindowGL::BeginDraw(bool clear)
		{
			if(clear)
				Clear();
		}

		void WindowGL::EndDraw()
		{
			glFlush();
			SwapBuffers(_hdc);
		}

		bool WindowGL::Update()
		{
			return WindowBase::Update();
		}

		void WindowGL::Close()
		{
			WindowBase::Close();
		}

		void WindowGL::MousePosition(int& x, int& y) const
		{
			x = 0, y = 0;
		}
	}
}

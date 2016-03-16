#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include "../opengl.org/wglext.h"

#include "../../../Assert/Assert.hpp"
#include "WindowWGL.hpp"

#pragma comment(lib, "OpenGL32.lib")

namespace Galatea
{
	namespace Display
	{
		PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

		void WindowWGL::UpdateStyle(WindowStyle style)
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

		void WindowWGL::InitOpenGL()
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

			wglChoosePixelFormatARB(_hdc, pf_attrib, NULL, 1u, &pixel_format, &num_formats);
			SetPixelFormat(_hdc, pixel_format, NULL);

			int c_attrib = 0;
			_gl_context = wglCreateContextAttribsARB(_hdc, NULL, &c_attrib);
			wglMakeCurrent(_hdc, _gl_context);

			SetWindowTextA(_hwnd, (char*)glGetString(GL_VERSION));
		}

		WindowWGL::WindowWGL(CStr title, int width, int height, WindowStyle style) : WindowGL{title, width, height}, WindowBase{title, width, height}
		{
			UpdateStyle(style);
			InitOpenGL();
			Initialize();
			Show();
		}

		WindowWGL::~WindowWGL()
		{
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(_gl_context);
			ReleaseDC(_hwnd, _hdc);
			DestroyWindow(_hwnd);
		}

		LRESULT WindowWGL::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
		{
			switch(msg)
			{
				case WM_LBUTTONDOWN: OnMouseDown(1); break;
				case WM_RBUTTONDOWN: OnMouseDown(2); break;
				case WM_MBUTTONDOWN: OnMouseDown(3); break;
				case WM_LBUTTONUP: OnMouseUp(1); break;
				case WM_RBUTTONUP: OnMouseUp(2); break;
				case WM_MBUTTONUP: OnMouseUp(3); break;
				case WM_MOUSEMOVE: OnMouseMove(LOWORD(lParam), HIWORD(lParam)); break;
			}

			return WindowBase::WndProc(msg, wParam, lParam);
		}

		void WindowWGL::BeginDraw(bool clear)
		{
			WindowGL::BeginDraw();

			if(clear)
				Clear();
 		}

		void WindowWGL::EndDraw()
		{
			WindowGL::EndDraw();

			glFlush();
			SwapBuffers(_hdc);
		}

		bool WindowWGL::Update()
		{
			return WindowGL::Update() && WindowBase::Update();
		}

		void WindowWGL::Close()
		{
			WindowGL::Close();
			WindowBase::Close();
		}

		void WindowWGL::MousePosition(int& x, int& y) const
		{
			POINT point;
			GetCursorPos(&point);
			x = point.x;
			y = point.y;
		}
	}
}

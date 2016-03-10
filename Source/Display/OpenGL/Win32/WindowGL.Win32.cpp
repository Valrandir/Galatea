#include "../../../Assert/Assert.hpp"
#include "../WindowGL.hpp"
#include "WindowWGL.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include "../opengl.org/wglext.h"
#include "../OpenGL.hpp"

namespace Galatea
{
	namespace Display
	{
		extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
		extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
		void InitOpenGLExtensions();

		namespace
		{
			inline void* LocalGetProcAddress(const char* fn_name)
			{
				return wglGetProcAddress(fn_name);
			}
		}

		WindowGL* WindowGL::Create(CStr title, int width, int height, WindowStyle style)
		{
			InitOpenGLExtensions();
			return new WindowWGL(title, width, height, style);
		}

		void InitOpenGLExtensions()
		{
			static bool is_initialized = false;
			if(is_initialized)
				return;

			WNDCLASSEX wc{};
			wc.cbSize = sizeof(wc);
			wc.style = CS_OWNDC;

			wc.lpfnWndProc = [](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hWnd, msg, wParam, lParam); };

			wc.hInstance = GetModuleHandle(NULL);
			wc.lpszClassName = TEXT("WindowGL.Win32");
			ASSERT(RegisterClassEx(&wc));

			HWND hwnd;
			HDC hdc;

			ASSERT(hwnd = CreateWindowEx(0, wc.lpszClassName, NULL, 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, NULL, wc.hInstance, NULL));
			ASSERT(hdc = GetDC(hwnd));

			PIXELFORMATDESCRIPTOR pixel_format_descriptor =
			{
				sizeof(PIXELFORMATDESCRIPTOR), 1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA, 32,
				0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				24, 8, 0,
				PFD_MAIN_PLANE,
				0, 0, 0, 0
			};

			int pixel_format = ChoosePixelFormat(hdc, &pixel_format_descriptor);
			SetPixelFormat(hdc, pixel_format, NULL);
			HGLRC wgl_context = wglCreateContext(hdc);
			wglMakeCurrent(hdc, wgl_context);

			if(!wglChoosePixelFormatARB)
			{
				#define WGL_GETPROC(type, name) name = (type)(wglGetProcAddress(#name))
				WGL_GETPROC(PFNWGLCHOOSEPIXELFORMATARBPROC, wglChoosePixelFormatARB);
				WGL_GETPROC(PFNWGLCREATECONTEXTATTRIBSARBPROC, wglCreateContextAttribsARB);
			}

			OpenGL::InitializeExtensions(LocalGetProcAddress);

			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(wgl_context);
			ReleaseDC(hwnd, hdc);
			DestroyWindow(hwnd);

			MSG msg;
			while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE));

			UnregisterClass(wc.lpszClassName, wc.hInstance);
			is_initialized = true;
		}
	}
}

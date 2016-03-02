#include "../../../Assert/Assert.hpp"
#include "../GLExt.hpp"

namespace Galatea
{
	namespace Display
	{
		//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		//{
		//	return DefWindowProc(hWnd, msg, wParam, lParam);
		//}

		const GLExt* GLExt::Create()
		{
			WNDCLASSEX wc{};
			wc.cbSize = sizeof(wc);
			wc.style = CS_OWNDC;

			//wc.lpfnWndProc = WndProc;

			wc.lpfnWndProc = [](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hWnd, msg, wParam, lParam); };

			wc.hInstance = GetModuleHandle(NULL);
			wc.lpszClassName = TEXT("GLExtWin32");
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

			GLExt* glext = new GLExt();

			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(wgl_context);
			ReleaseDC(hwnd, hdc);
			DestroyWindow(hwnd);

			MSG msg;
			while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE));

			return new GLExt();
		}
	}
}

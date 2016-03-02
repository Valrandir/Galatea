#include "WindowBase.hpp"

namespace Galatea
{
	namespace Display
	{
		namespace Common
		{
			void WindowBase::AdjustAndCenter(int& x, int& y, int& width, int& height, DWORD style)
			{
				RECT rect{0, 0, width, height};
				AdjustWindowRect(&rect, style, FALSE);
				width = rect.right - rect.left;
				height = rect.bottom - rect.top;
				x = (GetSystemMetrics(SM_CXSCREEN) - width) >> 1;
				y = (GetSystemMetrics(SM_CYSCREEN) - height) >> 1;
			}

			LRESULT CALLBACK WindowBase::WndProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
			{
				WindowBase* wb;

				if(msg != WM_NCCREATE && (wb = reinterpret_cast<WindowBase*>(GetWindowLongPtr(hWnd, GWLP_USERDATA))))
					return wb->WndProc(msg, wParam, lParam);

				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

			LRESULT WindowBase::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
			{
				switch(msg)
				{
					case WM_KEYDOWN:
						if(LOWORD(wParam) == VK_ESCAPE)
						{
							Close();
							return 0;
						}
						break;
					case WM_DESTROY:
						Close();
						return 0;
				}

				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

			WindowBase::WindowBase(LPCTSTR caption, int width, int height) : width{width}, height{height}, destroyed{}
			{
				const LPCTSTR CLASS_NAME = TEXT("WindowBase");
				HINSTANCE hInstance = GetModuleHandle(NULL);
				WNDCLASSEX wc;

				if(!GetClassInfoEx(hInstance, CLASS_NAME, &wc))
				{
					wc.cbSize = sizeof(wc);
					wc.style = CS_OWNDC;
					wc.lpfnWndProc = WndProcStatic;
					wc.cbClsExtra = 0;
					wc.cbWndExtra = 0;
					wc.hInstance = hInstance;
					wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
					wc.hCursor = LoadCursor(NULL, IDC_ARROW);
					wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);
					wc.lpszMenuName = NULL;
					wc.lpszClassName = CLASS_NAME;
					wc.hIconSm = NULL;

					RegisterClassEx(&wc);
				}

				int x, y;
				DWORD style = WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
				AdjustAndCenter(x, y, width, height, style);
				hWnd = CreateWindowEx(0, CLASS_NAME, caption, style, x, y, width, height, HWND_DESKTOP, NULL, hInstance, NULL);
				SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
				ShowWindow(hWnd, SW_SHOW);
			}

			WindowBase::~WindowBase() {}

			void WindowBase::SetCaption(LPCTSTR caption)
			{
				SetWindowText(hWnd, caption);
			}

			bool WindowBase::Update()
			{
				MSG msg;

				while(!destroyed && PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				return !destroyed;
			}

			void WindowBase::Close()
			{
				destroyed = true;
				DestroyWindow(hWnd);
				Update();
			}
		}
	}
}

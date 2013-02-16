#include "Window.hpp"

void Window::AdjustWindowRect(DWORD style, int& width, int& height)
{
	RECT rect = {0, 0, width, height};
	::AdjustWindowRect(&rect, style, FALSE);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
}

void Window::CenterWindowPos(int &x, int &y, int width, int height)
{
	x = (GetSystemMetrics(SM_CXSCREEN) - width) >> 1;
	y = (GetSystemMetrics(SM_CYSCREEN) - height) >> 1;
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(auto self = (Window*)GetWindowLong(hWnd, GWL_USERDATA))
		return self->WindowProc(hWnd, msg, wParam, lParam);
	else
		return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

void Window::Initialize(LPCTSTR title, int width, int height, DWORD style)
{
	WNDCLASSEX wc;
	int x, y;

	_hInst = GetModuleHandle(NULL);
	_width = width;
	_height = height;

	wc.cbSize = sizeof(wc);
	wc.style = 0U;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("Window");
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);

	CenterWindowPos(x, y, width, height);
	AdjustWindowRect(style, width, height);
	_hWnd = CreateWindow(wc.lpszClassName, title, style, x, y, width, height, HWND_DESKTOP, NULL, _hInst, NULL);

	SetWindowLong(_hWnd, GWL_USERDATA, (LONG)this);
}

Window::Window(LPCTSTR title, int width, int height, DWORD style)
{
	Initialize(title, width, height, style);
}

Window::Window(LPCTSTR title, int width, int height)
{
	Initialize(title, width, height, WS_OVERLAPPEDWINDOW);
}

void Window::Show()
{
	ShowWindow(_hWnd, SW_SHOW);
}

bool Window::Update()
{
	MSG msg;

	while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if(msg.message == WM_QUIT)
			return false;
	}

	return true;
}

void Window::Close()
{
	PostQuitMessage(0);
}

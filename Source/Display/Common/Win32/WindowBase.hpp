#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Galatea
{
	namespace Display
	{
		namespace Common
		{
			class WindowBase
			{
				void AdjustAndCenter(int& x, int& y, int& width, int& height, DWORD style);
				static LRESULT CALLBACK WndProcStatic(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

				protected:
				HWND _hwnd;
				bool _destroyed;
				int _width, _height;

				virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

				public:
				WindowBase(LPCTSTR caption, int width, int height, DWORD style = 0);
				virtual ~WindowBase();
				WindowBase(const WindowBase&) = delete;
				WindowBase& operator=(const WindowBase&) = delete;

				virtual void SetCaption(LPCTSTR caption);
				virtual void SetStyle(DWORD style);
				virtual void Show();
				virtual void Hide();
				virtual bool Update();
				virtual void Close();

				inline HWND GetHandle() const { return _hwnd; }
				inline int GetWidth() const { return _width; }
				inline int GetHeight() const { return _height; }
			};
		}
	}
}

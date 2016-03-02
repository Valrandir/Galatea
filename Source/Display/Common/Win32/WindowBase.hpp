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
				HWND hWnd;
				bool destroyed;
				int width, height;

				virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

				public:
				WindowBase(LPCTSTR caption, int width, int height);
				virtual ~WindowBase();
				WindowBase(const WindowBase&) = delete;
				WindowBase& operator=(const WindowBase&) = delete;

				virtual void SetCaption(LPCTSTR caption);
				virtual bool Update();
				virtual void Close();

				inline HWND GetHandle() const { return hWnd; }
				inline int GetWidth() const { return width; }
				inline int GetHeight() const { return height; }
			};
		}
	}
}

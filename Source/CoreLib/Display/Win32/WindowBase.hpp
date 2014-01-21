#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class WindowBase
{
	private:
	static void AdjustWindowRect(DWORD style, int& width, int& height);
	static void CenterWindowPos(int &x, int &y, int width, int height);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	protected:
	HINSTANCE _hInst;
	HWND _hWnd;
	int _width, _height;

	virtual LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
	void Initialize(LPCTSTR title, int width, int height, DWORD style);

	public:
	typedef void(*OnKeydownCallback)(unsigned int key_code, void* param);

	OnKeydownCallback _on_keydown_proc;
	void* _on_keydown_param;

	WindowBase(LPCTSTR title, int width, int height, DWORD style);
	WindowBase(LPCTSTR title, int width, int height);
	void Show();
	bool Update();
	void Close();

	void SetOnKeyDownCallback(OnKeydownCallback proc, void* param);
};

#pragma once
#include "BaseWindow.hpp"
#include "../../Types.hpp"

class AssertWnd : public BaseWindow
{
	static Galatea::Int const TEXTBOX_ID = 1;
	static Galatea::Int const BTN_COPY_ID = 2;
	static Galatea::Int const BTN_CLOSE_ID = 3;
	HWND _hText;
	HFONT _hFont;

	public:
	AssertWnd();
	~AssertWnd();
	LRESULT WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void SetText(LPCTSTR text);
	void ShowModal();

	private:
	void btnCopy_OnClick();
	void btnClose_OnClick();
};

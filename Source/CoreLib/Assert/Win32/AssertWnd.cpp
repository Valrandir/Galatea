#include "AssertWnd.hpp"
#include "../../String/String.hpp"

void ClipBoardSetText(LPCTSTR text);

AssertWnd::AssertWnd() : Window(TEXT("Assert Window"), 480, 360, WS_CAPTION | WS_SYSMENU)
{
	//Create Edit Control
	_hText = CreateWindowEx
	(
		WS_EX_CLIENTEDGE,
		TEXT("EDIT"),
		NULL,
		WS_VISIBLE | WS_CHILD | ES_READONLY | ES_MULTILINE | WS_HSCROLL | WS_VSCROLL,
		8,
		8,
		_width - 16,
		_height - 16 - 8 - 32,
		_hWnd,
		(HMENU)TEXTBOX_ID,
		_hInst,
		NULL
	);

	//Set Font
	_hFont = CreateFont(0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Courrier New"));
	if(_hFont)
		SendMessage(_hText, WM_SETFONT, (WPARAM)_hFont, 0);

	//Create Copy Button
	CreateWindow
	(
		TEXT("BUTTON"),
		TEXT("Copy"),
		WS_VISIBLE | WS_CHILD,
		_width - 8 - 96 - 8 - 96,
		_height - 8 - 32,
		96,
		32,
		_hWnd,
		(HMENU)BTN_COPY_ID,
		_hInst,
		NULL
	);

	//Create Close Button
	CreateWindow
	(
		TEXT("BUTTON"),
		TEXT("Close"),
		WS_VISIBLE | WS_CHILD,
		_width - 8 - 96,
		_height - 8 - 32,
		96,
		32,
		_hWnd,
		(HMENU)BTN_CLOSE_ID,
		_hInst,
		NULL
	);
}

AssertWnd::~AssertWnd()
{
	if(_hFont)
		DeleteObject(_hFont);
}

LRESULT AssertWnd::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_COMMAND:
			if(HIWORD(wParam) == BN_CLICKED)
				switch(LOWORD(wParam))
				{
					case BTN_COPY_ID: btnCopy_OnClick(); break;
					case BTN_CLOSE_ID: btnClose_OnClick(); break;
				}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

void AssertWnd::SetText(LPCTSTR text)
{
	SetWindowText(_hText, text);
}

void AssertWnd::ShowModal()
{
	Show();
	while(Update())
		Sleep(1U);
}

void AssertWnd::btnCopy_OnClick()
{
	Core::String string;
	int cch_length;

	cch_length = GetWindowTextLength(_hText);
	string.Reserve(cch_length + 1);
	GetWindowText(_hText, string.DrivePointer(cch_length), cch_length + 1);

	ClipBoardSetText(string.GetTChar());
}

void AssertWnd::btnClose_OnClick()
{
	Close();
}



#ifdef UNICODE
	#define CF_T_TEXT CF_UNICODETEXT
#else
	#define CF_T_TEXT CF_TEXT
#endif

void ClipBoardSetText(LPCTSTR text)
{
	SIZE_T bufferSize;
	HGLOBAL hClipMem;
	LPTSTR textBuffer;

	bufferSize = (lstrlen(text) + 1) * sizeof(TCHAR);
	hClipMem = GlobalAlloc(GMEM_MOVEABLE, bufferSize);
	textBuffer = (TCHAR*)GlobalLock(hClipMem);
	memcpy(textBuffer, text, bufferSize);
	GlobalUnlock(hClipMem);
	OpenClipboard(HWND_DESKTOP);
	EmptyClipboard();
	SetClipboardData(CF_T_TEXT, hClipMem);
	CloseClipboard();
}

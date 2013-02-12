#include "Assert.hpp"
#include "Win32/AssertWnd.hpp"
#include "../String/String.hpp"

void ShowAssertWindow(Core::String msg);

namespace Core
{
	void Fail(TChar const * failed_text, TChar const * function, TChar const * file, UInt line)
	{
		String msg;

		//msg = String::FormatStr
		//(
		//	Text("Failed Call : %s")
		//	Text("")
		//	NewLine
		//);

		msg = Text("Placeholder Message");
		ShowAssertWindow(msg);
	}
}

void ShowAssertWindow(Core::String msg)
{
	AssertWnd wnd;

	LPCTSTR text = 
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Users\\dlaplante\\Documents\\GitHub\\Core\\Project\\Visual Studio 2012\\CoreSpecimen\\Build\\CoreSpecimen32.exe'. Symbols loaded.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\ntdll.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\kernel32.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\KernelBase.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\user32.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\gdi32.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\lpk.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\usp10.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\msvcrt.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\advapi32.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\sechost.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\rpcrt4.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\sspicli.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\cryptbase.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\msvcr110d.dll'. Symbols loaded.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\msvcp110d.dll'. Symbols loaded.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\imm32.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\msctf.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\uxtheme.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\dwmapi.dll'. Cannot find or open the PDB file.\r\n"
		L"'CoreSpecimen32.exe' (Win32): Loaded 'C:\\Windows\\SysWOW64\\ole32.dll'. Cannot find or open the PDB file.\r\n"
		L"The program '[6996] CoreSpecimen32.exe' has exited with code 1 (0x1).\r\n"
	;

	wnd.SetText(text);
	wnd.ShowModal();

	ExitProcess(1U);
}

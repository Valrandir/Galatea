#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern void CoreSpecimen();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	CoreSpecimen();
	return 0;
}

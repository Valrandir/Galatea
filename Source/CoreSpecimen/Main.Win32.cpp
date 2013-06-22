#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern bool CoreSpecimen();

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR,  _In_ int)
{
	auto result = CoreSpecimen();
	return result ? 0 : 1;
}

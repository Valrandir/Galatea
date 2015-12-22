#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern bool TestMain();

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR,  _In_ int)
{
	auto result = TestMain();
	return result ? 0 : 1;
}

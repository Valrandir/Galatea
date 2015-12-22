#include "Keys.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Galatea
{
	namespace Input
	{
		unsigned int ToVirtualKeyCode(Keys key)
		{
			switch(key)
			{
				case Keys::KeyLeft: return VK_LEFT;
				case Keys::KeyRight: return VK_RIGHT;
				case Keys::KeyUp: return VK_UP;
				case Keys::KeyDown: return VK_DOWN;

				case Keys::KeyA: return 'A';
				case Keys::KeyB: return 'B';
				case Keys::KeyC: return 'C';
				case Keys::KeyD: return 'D';
				case Keys::KeyE: return 'E';
				case Keys::KeyF: return 'F';
				case Keys::KeyG: return 'G';
				case Keys::KeyH: return 'H';
				case Keys::KeyI: return 'I';
				case Keys::KeyJ: return 'J';
				case Keys::KeyK: return 'K';
				case Keys::KeyL: return 'L';
				case Keys::KeyM: return 'M';
				case Keys::KeyN: return 'N';
				case Keys::KeyO: return 'O';
				case Keys::KeyP: return 'P';
				case Keys::KeyQ: return 'Q';
				case Keys::KeyR: return 'R';
				case Keys::KeyS: return 'S';
				case Keys::KeyT: return 'T';
				case Keys::KeyU: return 'U';
				case Keys::KeyV: return 'V';
				case Keys::KeyW: return 'W';
				case Keys::KeyX: return 'X';
				case Keys::KeyY: return 'Y';
				case Keys::KeyZ: return 'Z';

				case Keys::KeyEscape: return VK_ESCAPE;
				case Keys::KeyReturn: return VK_RETURN;
				case Keys::KeySpace: return VK_SPACE;
			}

			return 0;
		}

		bool GetKeyState(Keys key)
		{
			return ::GetAsyncKeyState(ToVirtualKeyCode(key)) != 0;
		}
	}
}

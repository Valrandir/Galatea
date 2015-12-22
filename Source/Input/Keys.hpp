#pragma once

namespace Galatea
{
	namespace Input
	{
		enum class Keys
		{
			KeyLeft,
			KeyRight,
			KeyUp,
			KeyDown,

			KeyA,
			KeyB,
			KeyC,
			KeyD,
			KeyE,
			KeyF,
			KeyG,
			KeyH,
			KeyI,
			KeyJ,
			KeyK,
			KeyL,
			KeyM,
			KeyN,
			KeyO,
			KeyP,
			KeyQ,
			KeyR,
			KeyS,
			KeyT,
			KeyU,
			KeyV,
			KeyW,
			KeyX,
			KeyY,
			KeyZ,

			KeyEscape,
			KeyReturn,
			KeySpace
		};

		const unsigned int KeyMod_Shift = 0x1;
		const unsigned int KeyMod_Ctrl= 0x2;
		const unsigned int KeyMod_Alt = 0x4;

		enum class KeyDirection
		{
			Down,
			Up
		};

		struct KeyEvent
		{
			KeyDirection up_or_down;
			Keys key;
			unsigned int mod;
		};

		bool GetKeyState(Keys key);
	}
}

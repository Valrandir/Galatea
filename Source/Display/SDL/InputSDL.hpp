#pragma once
#include <SDL.h>
#include "../../Input/Keys.hpp"

namespace Galatea
{
	using namespace Input;

	namespace Display
	{
		KeyEvent ToKeyEvent(uint32_t sdl_event_type, SDL_Keysym sdl_keysym);
	}
}

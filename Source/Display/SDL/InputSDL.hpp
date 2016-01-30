#pragma once
#include <SDL.h>
#include "../../Input/Keys.hpp"

namespace Galatea
{
	namespace Display
	{
		Input::KeyEvent ToKeyEvent(uint32_t sdl_event_type, SDL_Keysym sdl_keysym);
	}
}

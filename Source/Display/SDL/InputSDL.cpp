#include "InputSDL.hpp"

namespace Galatea
{
	using namespace Input;

	namespace Display
	{
		KeyEvent ToKeyEvent(uint32_t sdl_event_type, SDL_Keysym sdl_keysym)
		{
			KeyEvent ke{};

			if(sdl_event_type == SDL_KEYDOWN)
				ke.up_or_down = KeyDirection::Down;
			else if(sdl_event_type == SDL_KEYUP)
				ke.up_or_down = KeyDirection::Up;
			else
				return ke;

			switch(sdl_keysym.sym)
			{
				case SDLK_LEFT: ke.key = Keys::KeyLeft; break;
				case SDLK_RIGHT: ke.key = Keys::KeyRight; break;
				case SDLK_UP: ke.key = Keys::KeyUp; break;

				case SDLK_a: ke.key = Keys::KeyA; break;
				case SDLK_b: ke.key = Keys::KeyB; break;
				case SDLK_c: ke.key = Keys::KeyC; break;
				case SDLK_d: ke.key = Keys::KeyD; break;
				case SDLK_e: ke.key = Keys::KeyE; break;
				case SDLK_f: ke.key = Keys::KeyF; break;
				case SDLK_g: ke.key = Keys::KeyG; break;
				case SDLK_h: ke.key = Keys::KeyH; break;
				case SDLK_i: ke.key = Keys::KeyI; break;
				case SDLK_j: ke.key = Keys::KeyJ; break;
				case SDLK_k: ke.key = Keys::KeyK; break;
				case SDLK_l: ke.key = Keys::KeyL; break;
				case SDLK_m: ke.key = Keys::KeyM; break;
				case SDLK_n: ke.key = Keys::KeyN; break;
				case SDLK_o: ke.key = Keys::KeyO; break;
				case SDLK_p: ke.key = Keys::KeyP; break;
				case SDLK_q: ke.key = Keys::KeyQ; break;
				case SDLK_r: ke.key = Keys::KeyR; break;
				case SDLK_s: ke.key = Keys::KeyS; break;
				case SDLK_t: ke.key = Keys::KeyT; break;
				case SDLK_u: ke.key = Keys::KeyU; break;
				case SDLK_v: ke.key = Keys::KeyV; break;
				case SDLK_w: ke.key = Keys::KeyW; break;
				case SDLK_x: ke.key = Keys::KeyX; break;
				case SDLK_y: ke.key = Keys::KeyY; break;
				case SDLK_z: ke.key = Keys::KeyZ; break;

				case SDLK_DOWN: ke.key = Keys::KeyDown; break;
				case SDLK_ESCAPE: ke.key = Keys::KeyEscape; break;
				case SDLK_RETURN: ke.key = Keys::KeyReturn; break;
				case SDLK_SPACE: ke.key = Keys::KeySpace; break;
			}

			if(sdl_keysym.mod | KMOD_LSHIFT || sdl_keysym.mod | KMOD_RSHIFT) ke.mod |= KeyMod_Shift;
			if(sdl_keysym.mod | KMOD_LCTRL || sdl_keysym.mod | KMOD_RCTRL) ke.mod |= KeyMod_Ctrl;
			if(sdl_keysym.mod | KMOD_LALT || sdl_keysym.mod | KMOD_RALT) ke.mod |= KeyMod_Alt;

			return ke;
		}
	}
}

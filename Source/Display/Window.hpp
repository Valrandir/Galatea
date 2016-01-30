#pragma once
#include <stdint.h>
#include "Color.hpp"
#include "Image.hpp"
#include "../Input/Input.hpp"

namespace Galatea
{
	namespace Display
	{
		#pragma warning(disable: 4250)
		class Window : public virtual Image
		{
			public:
			virtual ~Window();

			virtual Image* CreateImage(int width, int height) const = 0;
			virtual Image* CreateImage(const char* file) const = 0;
			virtual Image* CreateImage(const void* memory, Int size) const = 0;

			virtual void BeginDraw(bool clear = true) = 0;
			virtual void EndDraw() = 0;
			virtual bool Update() = 0;
			virtual void Close() = 0;
			virtual void MousePosition(int& x, int& y) const = 0;

			using OnKeyProc = void(*)(Input::KeyEvent ke, void* userdata);
			using OnMouseUpProc = void(*)(int button, void* userdata);
			using OnMouseDownProc = void(*)(int button, void* userdata);
			using OnMouseMoveProc = void(*)(int x, int y, void* userdata);
			OnKeyProc& OnKeyEvent(void* userdata = nullptr);
			OnMouseUpProc& OnMouseUpEvent(void* userdata = nullptr);
			OnMouseDownProc& OnMouseDownEvent(void* userdata = nullptr);
			OnMouseMoveProc& OnMouseMoveEvent(void* userdata = nullptr);

			protected:
			void OnKey(Input::KeyEvent ke);
			void OnMouseUp(int button);
			void OnMouseDown(int button);
			void OnMouseMove(int x, int y);

			private:
			struct OnKeyCallback { OnKeyProc proc; void* userdata; } _on_key{};
			struct OnMouseUpCallback { OnMouseUpProc proc; void* userdata; } _on_mouse_up{};
			struct OnMouseDownCallback { OnMouseDownProc proc; void* userdata; } _on_mouse_down{};
			struct OnMouseMoveCallback { OnMouseMoveProc proc; void* userdata; } _on_mouse_move{};
		};
	}
}

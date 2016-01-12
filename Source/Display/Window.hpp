#pragma once
#include <stdint.h>
#include "Color.hpp"
#include "Image.hpp"
#include "../Input/Input.hpp"

namespace Galatea
{
	namespace Display
	{
		using namespace Input;

		#pragma warning(disable: 4250)
		class Window : public virtual Image
		{
			public:
			virtual ~Window();

			virtual Image* CreateImage(int width, int height) const = 0;
			virtual Image* CreateImage(const char* file) const = 0;

			virtual void BeginDraw(bool clear = true) = 0;
			virtual void EndDraw() = 0;
			virtual bool Update() = 0;
			virtual void Close() = 0;

			using OnKeyProc = void(*)(KeyEvent ke, void* userdata);
			OnKeyProc& OnKeyEvent(void* userdata = nullptr);

			protected:
			void OnKey(KeyEvent ke);

			private:
			struct OnKeyCallback { OnKeyProc proc; void* userdata; } _on_key{};
		};
	}
}

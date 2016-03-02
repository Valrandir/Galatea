#pragma once
#include "../Window.hpp"
#include "ImageGL.hpp"

namespace Galatea
{
	namespace Display
	{
		class WindowGL : public Window, public ImageGL
		{
			bool _is_destroyed;

			WindowGL(CStr title, int width, int height, WindowStyle style);

			public:
			static WindowGL* Create(CStr title, int width, int height, WindowStyle style);
			~WindowGL();

			Image* CreateImage(int width, int height) const override;
			Image* CreateImage(const char* file) const override;
			Image* CreateImage(const void* memory, Int size) const override;

			void BeginDraw(bool clear = true) override;
			void EndDraw() override;
			bool Update() override;
			void Close() override;
			void MousePosition(int& x, int& y) const override;
		};
	}
}

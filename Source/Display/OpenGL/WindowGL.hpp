#pragma once
#include "../../Types.hpp"
#include "../Window.hpp"
#include "../WindowStyle.hpp"
#include "ImageGL.hpp"

namespace Galatea
{
	namespace Display
	{
		class WindowGL : public Window, public ImageGL
		{
			VectorDrawItem _vec_drawitem;

			unsigned int _program_id;
			unsigned int _vertex_buffer;

			protected:
			WindowGL(CStr title, int width, int height);

			public:
			static WindowGL* Create(CStr title, int width, int height, WindowStyle style);
			virtual ~WindowGL();

			void Initialize();

			Image* CreateImage(int width, int height) const override;
			Image* CreateImage(const char* file) const override;
			Image* CreateImage(const void* memory, Int size) const override;

			void BeginDraw(bool clear = true) override;
			void EndDraw() override;
			bool Update() override;
			void Close() override;
		};
	}
}

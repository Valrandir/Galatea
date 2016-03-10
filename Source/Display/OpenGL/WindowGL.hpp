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
			unsigned int _program_id;

			public:
			static WindowGL* Create(CStr title, int width, int height, WindowStyle style);
			WindowGL();
			virtual ~WindowGL();

			void Initialize();

			void BeginDraw(bool clear = true) override;
			void EndDraw() override;
			bool Update() override;
			void Close() override;
		};
	}
}

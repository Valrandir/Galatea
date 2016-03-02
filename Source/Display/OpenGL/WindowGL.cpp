#include "../../Assert/Assert.hpp"
#include "../Display.hpp"
#include "WindowGL.hpp"
#include "ImageGL.hpp"
#include "InputGL.hpp"

namespace Galatea
{
	namespace Display
	{
		WindowGL::~WindowGL()
		{
		}

		Image* WindowGL::CreateImage(int width, int height) const
		{
			return nullptr;
		}

		Image* WindowGL::CreateImage(const char* file) const
		{
			return nullptr;
		}

		Image* WindowGL::CreateImage(const void* memory, Int size) const
		{
			return nullptr;
		}

		void WindowGL::BeginDraw(bool clear)
		{
			if(clear)
				Clear();
		}

		void WindowGL::EndDraw()
		{
		}

		bool WindowGL::Update()
		{
			return true;
		}

		void WindowGL::Close()
		{
		}

		void WindowGL::MousePosition(int& x, int& y) const
		{
			x = 0, y = 0;
		}
	}
}

#pragma once
#include "Color.hpp"
#include "Image.hpp"
#include "Sprite.hpp"
#include "Window.hpp"

namespace Galatea
{
	namespace Display
	{
		Window* CreateWindow(const char* title, int width, int height);

		//Convert a file to a c++ variable initialized with its data in hex format.
		void FileToCppHex(const wchar_t* source_png_file, const wchar_t* target_cpp_file);
	}
}

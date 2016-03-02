#pragma once

namespace Galatea
{
	namespace Display
	{
		enum class WindowStyle
		{
			Borderless = 1,
			Caption = 2,
			SysMenu = 4,
			MinimizeBox = 8,
			MaximizeBox = 16
		};

		inline WindowStyle operator|(const WindowStyle& l, const WindowStyle& r)
		{
			return static_cast<WindowStyle>(static_cast<int>(l) | static_cast<int>(r));
		}

		inline bool operator&(const WindowStyle& l, const WindowStyle& r)
		{
			return 0 != (static_cast<int>(l) & static_cast<int>(r));
		}
	}
}

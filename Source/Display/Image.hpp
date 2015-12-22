#pragma once

namespace Galatea
{
	namespace Display
	{
		class Image
		{
			public:
			Image() = default;
			Image(const Image&) = delete;
			Image& operator=(const Image&) = delete;
			virtual ~Image();

			virtual int Width() const = 0;
			virtual int Height() const = 0;
		};
	}
}

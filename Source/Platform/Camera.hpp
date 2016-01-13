#pragma once
#include "../Geometry/Geometry.hpp"

namespace Galatea
{
	namespace Platform
	{
		using namespace Geometry;

		class Camera : public Rectangle, public Motion
		{
			public:
			Camera();
			~Camera();

			void Update();
		};
	}
}

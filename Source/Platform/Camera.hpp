#pragma once
#include "../Geometry/Geometry.hpp"

namespace Galatea
{
	namespace Platform
	{
		using namespace Geometry;

		class Camera
		{
			Rectangle area;
			Motion motion;

			public:
			Camera();
			Camera(const Vector& position, const Point& size);
			~Camera();

			void SetPosition(const Vector& position);
			void SetSize(const Point& size);
			void Impulse(const Vector& direction, double force);
			void Update();

			const Rectangle& Area() const;
		};
	}
}

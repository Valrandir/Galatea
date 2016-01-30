#pragma once
#include "../Geometry/Geometry.hpp"

namespace Galatea
{
	namespace Platform
	{
		class Camera
		{
			Geometry::Rectangle area;
			Geometry::Motion motion;

			public:
			Camera();
			Camera(const Geometry::Vector& position, const Geometry::Point& size);
			~Camera();

			void SetPosition(const Geometry::Vector& position);
			void SetSize(const Geometry::Point& size);
			void Impulse(const Geometry::Vector& direction, double force);
			void Update();
			
			double Friction() const;
			const Geometry::Rectangle& Area() const;
		};
	}
}

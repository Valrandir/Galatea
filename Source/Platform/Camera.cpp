#include "Camera.hpp"

namespace Galatea
{
	namespace Platform
	{
		using namespace Geometry;

		Camera::Camera()
		{
		}

		Camera::Camera(const Vector& position, const Point& size)
		{
			area.SetPosition(position.ToPoint());
			motion.SetPosition(position);
			area.SetSize(size);
		}

		Camera::~Camera()
		{
		}

		void Camera::SetPosition(const Vector& position)
		{
			area.SetPosition(position.ToPoint());
			motion.SetPosition(position);
		}

		void Camera::SetSize(const Point& size)
		{
			area.SetSize(size);
		}

		void Camera::Impulse(const Vector& direction, double force)
		{
			motion.Impulse(direction, force);
		}

		void Camera::Update()
		{
			motion.Update();
			area.SetPosition(motion.Position().ToPoint());
		}

		double Camera::Friction() const
		{
			return motion.Friction();
		}

		const Rectangle& Camera::Area() const
		{
			return area;
		}
	}
}

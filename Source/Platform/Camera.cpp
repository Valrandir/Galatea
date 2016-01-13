#include "Camera.hpp"

namespace Galatea
{
	namespace Platform
	{
		Camera::Camera()
		{
		}

		Camera::~Camera()
		{
		}

		void Camera::Update()
		{
			Motion::Update();
			Rectangle::SetPosition(Motion::Position().ToPoint());
		}
	}
}

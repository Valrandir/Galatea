#include "Motion.hpp"

namespace Galatea
{
	namespace Geometry
	{
		const double Motion::FRICTION_DEFAULT = 1. + 1. / 60.;

		Motion::Motion() : _position{}, _velocity{}, _mass{1.0}, _friction{FRICTION_DEFAULT}{}
		Motion::Motion(const Vector& position, const Vector& velocity, double mass) : _position{position}, _velocity{velocity}, _mass{mass < 1.0 ? 1.0 : mass} {}

		Motion::Motion(const Motion& src)
		{
			_position = src._position;
			_velocity = src._velocity;
			_mass = src._mass;
		}

		Motion& Motion::operator=(const Motion& src)
		{
			_position = src._position;
			_velocity = src._velocity;
			_mass = src._mass;
			return *this;
		}

		Motion& Motion::Impulse(Vector direction, double force)
		{
			_velocity += direction.Normalize() * (force / _mass);
			return *this;
		}

		void Motion::Update()
		{
			_velocity *= 1 / _friction;
			_velocity.EpsilonZero();

			_position += _velocity;
		}

		Vector Motion::Position() const { return _position; }
		Vector Motion::Velocity() const { return _velocity; }
		double Motion::Mass() const { return _mass; }
		double Motion::Friction() const { return _friction; }

		Motion& Motion::SetPosition(const Vector& position) { _position = position; return *this; }
		Motion& Motion::SetVelocity(const Vector& velocity) { _velocity = velocity; return *this; }
		Motion& Motion::SetMass(double mass) { _mass = mass < 1.0 ? 1.0 : mass; return *this; }
		Motion& Motion::SetFriction(double friction) { _friction = friction < 1.0 ? 1.0 : friction; return *this; }
	}
}

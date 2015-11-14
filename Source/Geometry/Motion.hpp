#pragma once
#include "Vector.hpp"

namespace Galatea
{
	namespace Geometry
	{
		class Motion
		{
			static const double FRICTION_DEFAULT;
			Vector _position;
			Vector _velocity;
			double _mass;
			double _friction;

			public:
			Motion();
			Motion(const Vector& position, const Vector& velocity, double mass = 1.0);

			Motion(const Motion& src);
			Motion& operator=(const Motion& src);

			Motion& Impulse(Vector direction, double force);
			void Update();

			Vector Position() const;
			Vector Velocity() const;
			double Mass() const;
			double Friction() const;

			Motion& SetPosition(const Vector& position);
			Motion& SetVelocity(const Vector& velocity);
			Motion& SetMass(double mass);
			Motion& SetFriction(double friction);
		};
	}
}

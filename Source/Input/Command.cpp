#include "Command.hpp"

namespace Galatea
{
	namespace Input
	{
		Command::Command(Int32 updates_per_second) : rate{updates_per_second}, triggered{}
		{
		}

		bool Command::Trigger()
		{
			if(triggered)
			{
				if(rate.Update())
				{
					rate.Reset();
					return true;
				}
				return false;
			}

			triggered = true;
			rate.Reset();
			return true;
		}

		bool Command::IsTriggered()
		{
			if(triggered && !rate.Update())
				return true;

			triggered = false;
			return false;
		}

		void Command::Reset()
		{
			triggered = false;
		}
	}
}

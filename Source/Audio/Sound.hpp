#pragma once

namespace Galatea
{
	namespace Audio
	{
		class Sound
		{
			public:
			virtual bool IsPlaying() const = 0;
			virtual ~Sound(){};
		};
	}
}

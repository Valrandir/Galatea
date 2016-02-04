#pragma once
#include "WaveData.hpp"

namespace Galatea
{
	namespace Audio
	{
		class AudioSystem
		{
			public:
			virtual void PlayTest(const WaveData& wave) = 0;
			virtual ~AudioSystem(){}

			static AudioSystem* Create();
		};
	}
}

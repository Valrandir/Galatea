#pragma once
#include "../AudioSystem.hpp"

namespace Galatea
{
	namespace Audio
	{
		class AudioSystemOpenAL : public AudioSystem
		{
			public:
			AudioSystemOpenAL();
			void PlayTest(const WaveData& wave) override;
		};
	}
}

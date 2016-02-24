#pragma once
#include "WaveData.hpp"
#include "Sound.hpp"

namespace Galatea
{
	namespace Audio
	{
		class AudioSystem
		{
			public:
			virtual const Sound* CreateSound(const WaveData& wave_data) = 0;
			virtual const Sound* CreateSound(const VoidPtr buffer, UInt buffer_size) = 0;
			virtual const Sound* CreateSound(CStr filename) = 0;
			virtual void PlaySound(const Sound* sound) = 0;

			virtual ~AudioSystem(){}
		};

		AudioSystem* CreateAudioSystem();
	}
}

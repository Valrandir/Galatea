#pragma once
#include "../AudioSystem.hpp"
#include <AL/alc.h>

namespace Galatea
{
	namespace Audio
	{
		class AudioSystemOpenAL : public AudioSystem
		{
			ALCdevice* _device;
			ALCcontext* _context;

			public:
			AudioSystemOpenAL();
			~AudioSystemOpenAL();
			AudioSystemOpenAL(const AudioSystemOpenAL&) = delete;
			AudioSystemOpenAL& operator=(const AudioSystemOpenAL&) = delete;

			const Sound* CreateSound(const WaveData& wave_data) override;
			const Sound* CreateSound(const VoidPtr buffer, UInt buffer_size) override;
			const Sound* CreateSound(CStr filename) override;
			void PlaySound(const Sound* sound) override;
		};
	}
}

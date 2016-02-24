#include "AudioSystemOpenAL.hpp"
#include "../../Assert/Assert.hpp"
#include "SoundOpenAL.hpp"

#include <AL/al.h>

namespace Galatea
{
	namespace Audio
	{
		AudioSystemOpenAL::AudioSystemOpenAL()
		{
			ASSERT(_device = alcOpenDevice(nullptr));
			ASSERT(_context = alcCreateContext(_device, nullptr));
			ASSERT(alcMakeContextCurrent(_context));
		}

		AudioSystemOpenAL::~AudioSystemOpenAL()
		{
			alcMakeContextCurrent(nullptr);
			alcDestroyContext(_context);
			alcCloseDevice(_device);
		}

		const Sound* AudioSystemOpenAL::CreateSound(const WaveData& wave_data)
		{
			alcGetError(_device);
			return new SoundOpenAL(wave_data);
		}

		const Sound* AudioSystemOpenAL::CreateSound(const VoidPtr buffer, UInt buffer_size)
		{
			alcGetError(_device);
			auto wave_data = WaveData::Create(buffer, buffer_size);
			auto sound = new SoundOpenAL(*wave_data);
			delete wave_data;
			return sound;
		}

		const Sound* AudioSystemOpenAL::CreateSound(CStr filename)
		{
			alcGetError(_device);
			auto wave_data = WaveData::Create(filename);
			auto sound = new SoundOpenAL(*wave_data);
			delete wave_data;
			return sound;
		}

		void AudioSystemOpenAL::PlaySound(const Sound* sound)
		{
			auto sound_openal = dynamic_cast<const SoundOpenAL*>(sound);

			alcGetError(_device);

			alSourcei(sound_openal->Source(), AL_BUFFER, sound_openal->Buffer());
			ASSERT(alGetError() == 0);

			alSourcePlay(sound_openal->Source());
			ASSERT(alGetError() == 0);
		}
	}
}

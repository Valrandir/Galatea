#pragma once
#include "SoundOpenAL.hpp"
#include "../../Assert/Assert.hpp"
#include <AL/alc.h>

namespace Galatea
{
	namespace Audio
	{
		SoundOpenAL::SoundOpenAL(const WaveData& wave_data)
		{
			alGenSources(1u, &_source);
			ASSERT(_source != 0);

			alSourcef(_source, AL_PITCH, 1);
			alSourcef(_source, AL_GAIN, 1);
			alSource3f(_source, AL_POSITION, 0, 0, 0);
			alSource3f(_source, AL_VELOCITY, 0, 0, 0);
			alSourcei(_source, AL_LOOPING, AL_FALSE);

			alGenBuffers(1u, &_buffer);
			ASSERT(_buffer != 0);

			auto& wf = wave_data.Format();
			ALenum format =
				wf.channels == 1 ?
				(wf.bits_per_sample == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16) :
				(wf.bits_per_sample == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16);

			alBufferData(_buffer, format, wave_data.Data(), ToInt32(wave_data.DataByteSize()), wf.samples_per_seconds);
			ASSERT(alGetError() == 0);
		}

		SoundOpenAL::~SoundOpenAL()
		{
			if(_source)
			{
				alDeleteSources(1, &_source);
				_source = 0;
			}

			if(_buffer)
			{
				alDeleteBuffers(1, &_buffer);
				_buffer = 0;
			}
		}

		bool SoundOpenAL::IsPlaying() const
		{
			ALint state;
			alGetSourcei(_source, AL_SOURCE_STATE, &state);
			ASSERT(alGetError() == 0);
			return state == AL_PLAYING;
		}
	}
}

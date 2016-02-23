#include "AudioSystemOpenAL.hpp"
#include "../../Timing/Timing.hpp"

#include <AL/al.h>
#include <AL/alc.h>

#define Assert(fn) if(!(fn)) throw;

namespace Galatea
{
	namespace Audio
	{
		AudioSystemOpenAL::AudioSystemOpenAL()
		{

		}

		void AudioSystemOpenAL::PlayTest(const WaveData& wave)
		{
			//http://enigma-dev.org/forums/index.php?topic=730.0;wap2
			//OpenAL Soft

			ALCdevice *device;
			ALCcontext *context;
			ALenum err;

			Assert(device = alcOpenDevice(nullptr));
			Assert(context = alcCreateContext(device, nullptr));
			Assert(alcMakeContextCurrent(context));

			ALuint source;
			alGenSources(1u, &source);
			alSourcef(source, AL_PITCH, 1);
			alSourcef(source, AL_GAIN, 1);
			alSource3f(source, AL_POSITION, 0, 0, 0);
			alSource3f(source, AL_VELOCITY, 0, 0, 0);
			alSourcei(source, AL_LOOPING, AL_FALSE);

			ALuint buffer;
			alGenBuffers(1u, &buffer);

			auto& wf = wave.Format();
			ALsizei size = wave.DataByteSize();
			ALsizei freq = wf.samples_per_seconds;
			ALenum format =
				wf.channels == 1 ?
					(wf.bits_per_sample == 8 ? AL_FORMAT_MONO8 : AL_FORMAT_MONO16) :
					(wf.bits_per_sample == 8 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16);

			ALvoid *data = wave.Data();
			ALboolean loop = AL_FALSE;

			alcGetError(device);
			alBufferData(buffer, format, data, size, freq);
			err = alGetError();

			alSourcei(source, AL_BUFFER, buffer);
			err = alGetError();

			alSourcePlay(source);
			err = alGetError();

			ALint source_state;
			alGetSourcei(source, AL_SOURCE_STATE, &source_state);
			err = alGetError();
			while(source_state == AL_PLAYING)
			{
				Timing::Sleep(25);
				alGetSourcei(source, AL_SOURCE_STATE, &source_state);
				err = alGetError();
			}

			alDeleteSources(1, &source);
			alDeleteBuffers(1, &buffer);
			device = alcGetContextsDevice(context);
			alcMakeContextCurrent(nullptr);
			alcDestroyContext(context);
			alcCloseDevice(device);
		}
	}
}

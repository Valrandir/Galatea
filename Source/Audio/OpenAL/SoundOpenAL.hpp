#pragma once
#include "../Sound.hpp"
#include "../WaveData.hpp"
#include <AL/al.h>

namespace Galatea
{
	namespace Audio
	{
		class SoundOpenAL : public Sound
		{
			ALuint _source;
			ALuint _buffer;

			public:
			SoundOpenAL(const WaveData& wave_data);
			~SoundOpenAL();
			SoundOpenAL(const SoundOpenAL&) = delete;
			SoundOpenAL& operator=(const SoundOpenAL&) = delete;

			bool IsPlaying() const override;
			inline ALuint Source() const { return _source; }
			inline ALuint Buffer() const { return _buffer; }
		};
	}
}

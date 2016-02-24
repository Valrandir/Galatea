#include "AudioSystem.hpp"
#include "OpenAL/AudioSystemOpenAL.hpp"

namespace Galatea
{
	namespace Audio
	{
		AudioSystem* CreateAudioSystem()
		{
			return new AudioSystemOpenAL();
		}
	}
}

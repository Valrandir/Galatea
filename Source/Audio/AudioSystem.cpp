#include "AudioSystem.hpp"
#include "OpenAL/AudioSystemOpenAL.hpp"

namespace Galatea
{
	namespace Audio
	{
		AudioSystem* AudioSystem::Create()
		{
			return new AudioSystemOpenAL();
		}
	}
}

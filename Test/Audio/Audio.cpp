#include "../Galatea.hpp"
using namespace Galatea;
using namespace Audio;

Bool AudioTest()
{
	Bool result = true;

	auto filepath = LR"(D:\Dev\Flac\sample.wav)";
	auto waveData = WaveData::FromFile(filepath);

	auto audio = AudioSystem::Create();
	audio->PlayTest(*waveData);
	delete audio;

	delete waveData;

	return result;
}

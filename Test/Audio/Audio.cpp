#include "../Galatea.hpp"
using namespace Galatea;

void audio_data(void*& buffer, Int32& buffer_size);

Bool PlaySingle()
{
	void* buffer;
	Int32 buffer_size;
	audio_data(buffer, buffer_size);

	auto audio_sys = Audio::CreateAudioSystem();
	auto sound = audio_sys->CreateSound(buffer, buffer_size);

	audio_sys->PlaySound(sound);

	while(sound->IsPlaying())
		Timing::Sleep(10);

	delete sound;
	delete audio_sys;

	return true;
}

Bool PlayMultiple()
{
	void* buffer;
	Int32 buffer_size;
	audio_data(buffer, buffer_size);

	auto audio_sys = Audio::CreateAudioSystem();
	Audio::WaveData* wave_data = Audio::WaveData::Create(buffer, buffer_size);

	const Audio::Sound* sounds[] =
	{
		audio_sys->CreateSound(*wave_data),
		audio_sys->CreateSound(*wave_data),
		audio_sys->CreateSound(*wave_data)
	};

	for(auto& snd : sounds)
	{
		audio_sys->PlaySound(snd);
		Timing::Sleep(256);
	}

	bool is_playing = true;

	while(is_playing)
	{
		is_playing = false;

		for(auto& snd : sounds)
			if(snd->IsPlaying())
			{
				is_playing = true;
				Timing::Sleep(25);
				break;
			}
	}

	for(auto& snd : sounds)
		delete snd;

	delete audio_sys;

	return true;
}

Bool AudioTest()
{
	Bool result = true;

	CHECK(PlaySingle());
	CHECK(PlayMultiple());

	return result;
}

void audio_data(void*& buffer, Int32& buffer_size)
{
	//Sample wave file with headers. 8 bits mono.
	static UInt8 data[] =
	{
		0x52,0x49,0x46,0x46,0xa6,0x09,0x00,0x00,0x57,0x41,0x56,0x45,0x66,0x6d,0x74,0x20,
		0x10,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x40,0x1f,0x00,0x00,0x40,0x1f,0x00,0x00,
		0x01,0x00,0x08,0x00,0x4c,0x49,0x53,0x54,0x1a,0x00,0x00,0x00,0x49,0x4e,0x46,0x4f,
		0x49,0x53,0x46,0x54,0x0e,0x00,0x00,0x00,0x4c,0x61,0x76,0x66,0x35,0x37,0x2e,0x32,
		0x36,0x2e,0x31,0x30,0x30,0x00,0x64,0x61,0x74,0x61,0x60,0x09,0x00,0x00,0x81,0xec,
		0x30,0x6e,0x90,0x56,0x29,0x5b,0x92,0x28,0x46,0x79,0x89,0x76,0x2c,0x49,0x7e,0x67,
		0xab,0x66,0xb4,0x74,0xb4,0x92,0x70,0x9f,0x90,0xfb,0x39,0x99,0xbd,0xba,0xc0,0x1c,
		0xae,0x6c,0x52,0x23,0x8f,0x58,0x25,0x53,0x86,0x7d,0x62,0x22,0x78,0x66,0x91,0x8b,
		0x89,0xb3,0x7b,0xc6,0x7d,0xa9,0x6d,0xc3,0xae,0x31,0xd1,0x99,0xe1,0x58,0x53,0xad,
		0x55,0x43,0x44,0x98,0x2e,0x3a,0x6b,0x8a,0x77,0x47,0x39,0x88,0x64,0xa6,0x74,0xba,
		0x8e,0x9e,0xac,0x8d,0xb8,0x5e,0xdb,0x55,0x73,0xce,0xa2,0xce,0x27,0xa4,0x7c,0x59,
		0x2a,0x78,0x70,0x24,0x4d,0x81,0x82,0x72,0x24,0x67,0x79,0x7f,0x9b,0x83,0xc8,0x72,
		0xc3,0x76,0xb0,0x94,0x84,0xcf,0x27,0xbe,0xa4,0xca,0x8e,0x49,0xb5,0x5c,0x4f,0x2d,
		0x97,0x3d,0x33,0x63,0x8a,0x7e,0x57,0x25,0x8f,0x64,0xa3,0x7d,0xad,0xa0,0x86,0xbb,
		0x49,0xc5,0x69,0xdf,0x7d,0x4b,0xd9,0x91,0xe0,0x4a,0x87,0x94,0x56,0x33,0x59,0x85,
		0x21,0x49,0x77,0x89,0x7a,0x39,0x58,0x8d,0x6f,0xa9,0x72,0xc8,0x71,0xba,0x74,0x67,
		0xa1,0x76,0xf0,0x28,0xa4,0xb5,0xb2,0xb9,0x2c,0xb3,0x69,0x52,0x29,0x86,0x53,0x28,
		0x5d,0x87,0x85,0x6d,0x30,0x89,0x73,0x91,0x8c,0x92,0xb7,0x6d,0xc7,0x44,0xad,0x6f,
		0xaa,0xa4,0x2b,0xdb,0x8f,0xdd,0x60,0x56,0xb4,0x4c,0x46,0x3c,0x90,0x27,0x41,0x70,
		0x8f,0x83,0x55,0x47,0x9a,0x68,0xa5,0x70,0xbb,0x83,0x97,0x9d,0x57,0xce,0x52,0xdf,
		0x51,0x73,0xd2,0x94,0xd5,0x27,0xa4,0x81,0x4a,0x30,0x66,0x70,0x1c,0x5d,0x82,0x91,
		0x7d,0x3e,0x75,0x8a,0x76,0x9b,0x75,0xc3,0x62,0xc0,0x5f,0x96,0xa2,0x7e,0xe9,0x1b,
		0xc7,0xa3,0xbd,0x96,0x3a,0xc0,0x50,0x4a,0x2f,0x86,0x40,0x31,0x75,0x8f,0x91,0x6c,
		0x42,0x99,0x6d,0x8f,0x7b,0x94,0xa0,0x71,0xbf,0x3d,0xc8,0x6c,0xd6,0x96,0x35,0xeb,
		0x84,0xd7,0x4f,0x74,0xa6,0x3a,0x3f,0x49,0x82,0x21,0x54,0x87,0x96,0x8f,0x54,0x62,
		0x98,0x64,0x97,0x69,0xb2,0x74,0xa2,0x8a,0x5d,0xc5,0x68,0xf2,0x3a,0x8a,0xcf,0x8f,
		0xc4,0x26,0xaa,0x74,0x36,0x3a,0x6b,0x62,0x23,0x76,0x94,0x9a,0x83,0x46,0x87,0x7c,
		0x6f,0x86,0x75,0xb0,0x6b,0xc1,0x5a,0x9d,0x9f,0x94,0xce,0x1d,0xce,0xa0,0xb0,0x83,
		0x3a,0xbf,0x46,0x37,0x45,0x7b,0x3c,0x3e,0x90,0x9b,0x9a,0x6c,0x51,0x95,0x61,0x7f,
		0x71,0x94,0x95,0x88,0xb3,0x54,0xc6,0x78,0xcb,0x7e,0x41,0xe3,0x8a,0xbd,0x4b,0x76,
		0xa3,0x2c,0x38,0x5e,0x70,0x2d,0x66,0xa1,0x9e,0x93,0x54,0x6b,0x87,0x59,0x80,0x70,
		0xa9,0x82,0xb0,0x8a,0x78,0xb8,0x7b,0xd3,0x36,0x87,0xd0,0x93,0xa6,0x3d,0xa2,0x74,
		0x22,0x40,0x73,0x53,0x37,0x8b,0xaa,0x9e,0x81,0x4a,0x7f,0x6a,0x5f,0x79,0x85,0xa9,
		0x8c,0xbf,0x6a,0x9f,0x93,0x99,0xa2,0x29,0xc1,0xb3,0xa6,0x7a,0x57,0xab,0x47,0x1e,
		0x54,0x78,0x3a,0x56,0xa8,0xab,0x99,0x67,0x52,0x80,0x55,0x69,0x76,0xa2,0x9f,0xa8,
		0xaa,0x69,0xa9,0x7b,0xb1,0x63,0x55,0xd8,0xa9,0xa5,0x57,0x7e,0x8d,0x25,0x24,0x6e,
		0x6a,0x38,0x80,0xbb,0xa7,0x89,0x4d,0x5f,0x6d,0x50,0x72,0x8a,0xb5,0x9d,0xbc,0x84,
		0x78,0x92,0x80,0xa6,0x40,0x93,0xd7,0xae,0x89,0x53,0x93,0x60,0x12,0x3a,0x83,0x59,
		0x4d,0xa7,0xbf,0x9b,0x6c,0x42,0x66,0x5a,0x5d,0x7c,0xa9,0xb8,0xa8,0xb3,0x67,0x81,
		0x7b,0x96,0x84,0x4f,0xc8,0xcf,0xa9,0x62,0x60,0x89,0x37,0x10,0x5d,0x8b,0x50,0x6e,
		0xc0,0xb6,0x83,0x4c,0x46,0x64,0x56,0x70,0x94,0xc3,0xb0,0xaf,0x8d,0x5b,0x7b,0x78,
		0xa7,0x69,0x7d,0xde,0xc6,0x8c,0x45,0x71,0x70,0x1d,0x24,0x87,0x88,0x52,0x8d,0xc6,
		0xa1,0x63,0x37,0x54,0x62,0x61,0x84,0xb1,0xc9,0xa7,0xa5,0x66,0x5f,0x73,0x93,0xa4,
		0x63,0xaa,0xdd,0xb5,0x5f,0x41,0x7d,0x57,0x15,0x4a,0xa2,0x79,0x59,0xa2,0xc0,0x89,
		0x44,0x36,0x63,0x66,0x75,0x98,0xc7,0xbc,0x9e,0x86,0x50,0x68,0x7c,0xb1,0x93,0x72,
		0xc3,0xcf,0x95,0x39,0x4f,0x7f,0x43,0x1e,0x72,0xa8,0x68,0x66,0xaf,0xb5,0x70,0x2d,
		0x43,0x6e,0x71,0x83,0xac,0xcf,0xaa,0x92,0x63,0x50,0x70,0x96,0xbe,0x7e,0x88,0xc6,
		0xbf,0x6e,0x2b,0x66,0x7a,0x37,0x33,0x91,0x9d,0x5f,0x76,0xb6,0xa7,0x54,0x23,0x53,
		0x78,0x80,0x92,0xbd,0xc5,0x9a,0x79,0x4b,0x5f,0x82,0xb8,0xb3,0x72,0x96,0xc2,0xab,
		0x4b,0x35,0x79,0x6f,0x30,0x4d,0xa0,0x8c,0x5f,0x87,0xb7,0x93,0x3a,0x25,0x62,0x86,
		0x91,0xa0,0xc3,0xb1,0x8b,0x5d,0x49,0x72,0x9e,0xcc,0x95,0x6d,0x9f,0xc0,0x93,0x38,
		0x47,0x7e,0x5f,0x32,0x6a,0xa2,0x7e,0x68,0x96,0xb1,0x7a,0x26,0x30,0x72,0x99,0x9f,
		0xab,0xb9,0x9b,0x79,0x4b,0x56,0x86,0xbe,0xc6,0x75,0x6e,0xa7,0xc0,0x78,0x2f,0x56,
		0x79,0x52,0x43,0x83,0x99,0x74,0x75,0xa0,0xa4,0x5b,0x1d,0x44,0x86,0xaa,0xa8,0xad,
		0xa4,0x8a,0x69,0x4a,0x6c,0x9e,0xd2,0xa8,0x5e,0x77,0xb7,0xbc,0x5c,0x31,0x5f,0x70,
		0x50,0x5e,0x91,0x89,0x6f,0x84,0xa6,0x8f,0x3d,0x21,0x5b,0x9d,0xb5,0xab,0xa4,0x8f,
		0x7e,0x5c,0x57,0x7f,0xb6,0xcf,0x82,0x59,0x8a,0xc7,0xa5,0x41,0x36,0x63,0x6a,0x5a,
		0x79,0x8f,0x77,0x71,0x96,0xa8,0x72,0x26,0x2e,0x76,0xb3,0xb8,0xa7,0x92,0x80,0x75,
		0x5b,0x6a,0x91,0xc7,0xb6,0x65,0x63,0xa3,0xca,0x80,0x30,0x41,0x69,0x68,0x6b,0x87,
		0x82,0x6b,0x7e,0xa6,0x9e,0x50,0x1c,0x47,0x96,0xc2,0xb3,0x9c,0x82,0x7b,0x6d,0x61,
		0x7a,0xa4,0xca,0x92,0x5a,0x79,0xbb,0xb8,0x58,0x2e,0x52,0x6e,0x68,0x7a,0x8a,0x75,
		0x6d,0x90,0xac,0x82,0x30,0x26,0x68,0xaf,0xbe,0xa8,0x90,0x7b,0x79,0x64,0x69,0x89,
		0xb8,0xbb,0x72,0x60,0x96,0xc6,0x91,0x3b,0x3c,0x65,0x6b,0x69,0x84,0x85,0x6f,0x78,
		0x9f,0xa2,0x60,0x25,0x42,0x89,0xb8,0xb2,0xa0,0x8a,0x7d,0x6f,0x5e,0x74,0x9d,0xc5,
		0x9c,0x61,0x74,0xb0,0xb8,0x64,0x37,0x57,0x6e,0x61,0x70,0x8c,0x7f,0x6f,0x87,0xa3,
		0x89,0x41,0x30,0x63,0x9d,0xaf,0xa6,0x9e,0x8a,0x7b,0x5f,0x60,0x84,0xb3,0xbe,0x7a,
		0x63,0x91,0xbb,0x91,0x45,0x4b,0x6e,0x65,0x58,0x7e,0x91,0x78,0x76,0x96,0x9c,0x68,
		0x33,0x4a,0x7f,0xa2,0xa2,0xa4,0x9d,0x89,0x6e,0x56,0x6d,0x95,0xbe,0xa2,0x6a,0x7c,
		0xa9,0xaa,0x62,0x45,0x6b,0x70,0x51,0x60,0x90,0x8a,0x72,0x84,0xa0,0x89,0x4a,0x3b,
		0x67,0x8f,0x9a,0x9f,0xaa,0x9a,0x80,0x5f,0x5b,0x7c,0xa4,0xb7,0x84,0x72,0x99,0xad,
		0x82,0x49,0x5f,0x7b,0x5d,0x4b,0x7a,0x94,0x78,0x75,0x99,0x9d,0x68,0x3b,0x53,0x7b,
		0x8c,0x94,0xa7,0xac,0x91,0x75,0x58,0x69,0x88,0xac,0xa2,0x77,0x8b,0xa9,0x9b,0x5e,
		0x4f,0x79,0x70,0x4a,0x5f,0x92,0x85,0x6c,0x88,0xa5,0x87,0x4e,0x48,0x6d,0x7f,0x86,
		0x98,0xb1,0xa2,0x88,0x6b,0x5e,0x74,0x8f,0xaa,0x8a,0x80,0xa4,0xa8,0x7c,0x4d,0x67,
		0x7b,0x57,0x4b,0x7f,0x91,0x6f,0x77,0x9f,0x9a,0x68,0x48,0x60,0x74,0x79,0x88,0xa5,
		0xad,0x96,0x83,0x66,0x68,0x7a,0x97,0x9a,0x7c,0x97,0xaf,0x98,0x62,0x57,0x7a,0x68,
		0x48,0x65,0x91,0x7c,0x6c,0x91,0xa2,0x82,0x58,0x56,0x6f,0x72,0x7b,0x92,0xab,0xa1,
		0x91,0x7c,0x66,0x71,0x81,0x9a,0x84,0x82,0xad,0xaa,0x82,0x5a,0x6c,0x75,0x50,0x4e,
		0x80,0x89,0x6c,0x80,0xa1,0x93,0x6e,0x56,0x64,0x6f,0x71,0x82,0x9b,0xa6,0x98,0x91,
		0x73,0x6d,0x78,0x89,0x8e,0x75,0x97,0xb1,0x9b,0x72,0x63,0x79,0x63,0x46,0x63,0x87,
		0x75,0x71,0x96,0x9f,0x83,0x65,0x5d,0x6d,0x6c,0x75,0x88,0x9f,0x9f,0x97,0x8b,0x70,
		0x78,0x7d,0x8c,0x7b,0x7a,0xa8,0xa7,0x8d,0x6b,0x75,0x77,0x51,0x4e,0x75,0x7d,0x6a,
		0x83,0xa0,0x94,0x7a,0x63,0x68,0x6f,0x6c,0x7a,0x8e,0x9d,0x97,0x98,0x81,0x78,0x7f,
		0x82,0x87,0x6c,0x8d,0xa9,0x99,0x80,0x6f,0x7f,0x68,0x4b,0x5f,0x7b,0x6c,0x6e,0x94,
		0x9b,0x8b,0x73,0x65,0x70,0x6c,0x70,0x7e,0x92,0x96,0x96,0x93,0x7b,0x84,0x80,0x89,
		0x77,0x6f,0x9e,0x9d,0x8f,0x76,0x7b,0x80,0x5b,0x54,0x6f,0x72,0x64,0x7c,0x96,0x93,
		0x85,0x6d,0x6f,0x75,0x6c,0x76,0x81,0x90,0x8f,0x96,0x86,0x82,0x8a,0x85,0x8a,0x6a,
		0x84,0x9d,0x91,0x85,0x73,0x86,0x73,0x57,0x63,0x75,0x67,0x68,0x87,0x92,0x8c,0x7b,
		0x6f,0x7a,0x73,0x72,0x7a,0x85,0x8c,0x8c,0x91,0x7e,0x8c,0x86,0x8e,0x7e,0x6d,0x96,
		0x91,0x8d,0x76,0x7a,0x86,0x65,0x5e,0x6f,0x72,0x63,0x74,0x8b,0x8d,0x86,0x73,0x76,
		0x7d,0x73,0x79,0x7c,0x89,0x85,0x8f,0x85,0x81,0x8f,0x88,0x92,0x6f,0x82,0x96,0x8c,
		0x85,0x6e,0x86,0x78,0x61,0x69,0x75,0x6b,0x67,0x7e,0x8b,0x89,0x7c,0x71,0x7e,0x79,
		0x79,0x7b,0x82,0x88,0x85,0x8b,0x7b,0x8c,0x88,0x91,0x85,0x70,0x93,0x8c,0x8e,0x76,
		0x77,0x85,0x6a,0x65,0x6f,0x75,0x65,0x70,0x83,0x89,0x83,0x73,0x77,0x80,0x79,0x7e,
		0x7d,0x87,0x82,0x89,0x82,0x7e,0x8e,0x88,0x95,0x74,0x83,0x93,0x8c,0x86,0x6e,0x84,
		0x79,0x67,0x69,0x76,0x6f,0x67,0x7a,0x85,0x86,0x7b,0x72,0x7e,0x7d,0x7e,0x7f,0x83,
		0x86,0x81,0x89,0x78,0x88,0x88,0x91,0x89,0x73,0x91,0x8c,0x8e,0x77,0x76,0x84,0x6f,
		0x68,0x6f,0x77,0x69,0x6e,0x7e,0x85,0x82,0x74,0x77,0x81,0x7d,0x81,0x7e,0x88,0x82,
		0x87,0x80,0x7c,0x8a,0x86,0x95,0x78,0x83,0x91,0x8d,0x88,0x70,0x81,0x7b,0x6c,0x6a,
		0x76,0x71,0x69,0x76,0x81,0x83,0x7b,0x71,0x7d,0x80,0x80,0x81,0x83,0x88,0x80,0x87,
		0x78,0x85,0x85,0x8f,0x8b,0x76,0x8e,0x8c,0x90,0x7b,0x77,0x84,0x74,0x6b,0x6f,0x78,
		0x6c,0x6d,0x7b,0x82,0x7f,0x74,0x75,0x80,0x7f,0x84,0x82,0x89,0x82,0x84,0x81,0x7a,
		0x87,0x85,0x93,0x7c,0x7f,0x8e,0x8d,0x89,0x73,0x7f,0x7d,0x71,0x6c,0x76,0x74,0x69,
		0x73,0x7d,0x81,0x79,0x70,0x7a,0x7f,0x80,0x83,0x85,0x88,0x82,0x87,0x7a,0x82,0x84,
		0x8b,0x8c,0x77,0x89,0x8c,0x8f,0x7e,0x76,0x82,0x77,0x6f,0x70,0x79,0x6f,0x6d,0x78,
		0x7f,0x7e,0x73,0x72,0x7e,0x7e,0x83,0x82,0x89,0x85,0x85,0x82,0x7a,0x86,0x84,0x90,
		0x7f,0x7d,0x8c,0x8b,0x8a,0x76,0x7d,0x7f,0x74,0x6f,0x77,0x77,0x6c,0x72,0x7c,0x7e,
		0x79,0x70,0x77,0x7e,0x80,0x84,0x85,0x8a,0x83,0x86,0x7c,0x80,0x85,0x89,0x8c,0x79,
		0x84,0x8a,0x8c,0x80,0x76,0x81,0x7a,0x72,0x71,0x7a,0x72,0x6e,0x77,0x7e,0x7d,0x74,
		0x70,0x7b,0x7d,0x82,0x83,0x88,0x86,0x84,0x84,0x7b,0x85,0x84,0x8f,0x83,0x7b,0x8a,
		0x8a,0x8a,0x78,0x7b,0x80,0x76,0x70,0x77,0x7a,0x70,0x72,0x7b,0x7f,0x79,0x6f,0x73,
		0x7d,0x7e,0x82,0x84,0x89,0x84,0x86,0x7f,0x7f,0x85,0x88,0x8d,0x7b,0x82,0x8a,0x8b,
		0x82,0x76,0x7f,0x7c,0x73,0x72,0x7a,0x76,0x6f,0x76,0x7d,0x7d,0x75,0x6f,0x78,0x7c,
		0x81,0x82,0x87,0x87,0x84,0x85,0x7c,0x83,0x84,0x8d,0x86,0x7c,0x87,0x8a,0x8a,0x7a,
		0x79,0x7f,0x79,0x72,0x75,0x7a,0x73,0x72,0x7a,0x7f,0x7a,0x71,0x72,0x7b,0x7e,0x82,
		0x83,0x88,0x85,0x85,0x80,0x7f,0x84,0x87,0x8d,0x7e,0x80,0x8a,0x8a,0x84,0x76,0x7e,
		0x7d,0x75,0x72,0x7a,0x79,0x71,0x76,0x7d,0x7d,0x75,0x6f,0x76,0x7b,0x80,0x81,0x86,
		0x87,0x83,0x85,0x7d,0x82,0x84,0x8b,0x88,0x7b,0x86,0x8a,0x8a,0x7d,0x78,0x80,0x79,
		0x74,0x75,0x7c,0x74,0x72,0x79,0x7e,0x7b,0x72,0x71,0x79,0x7c,0x81,0x82,0x87,0x85,
		0x85,0x82,0x7e,0x85,0x86,0x8d,0x82,0x7f,0x89,0x8a,0x86,0x78,0x7c,0x7f,0x76,0x73,
		0x79,0x79,0x73,0x75,0x7c,0x7e,0x78,0x70,0x74,0x7b,0x7e,0x81,0x83,0x87,0x84,0x85,
		0x7e,0x81,0x85,0x89,0x8a,0x7e,0x84,0x8a,0x8a,0x80,0x78,0x7f,0x7b,0x74,0x76,0x7c,
		0x76,0x73,0x78,0x7d,0x7b,0x74,0x71,0x78,0x7c,0x7f,0x81,0x86,0x85,0x84,0x83,0x7e,
		0x84,0x85,0x8c,0x84,0x7f,0x87,0x8a,0x87,0x7a,0x7b,0x7e,0x78,0x73,0x79,0x7b,0x74,
		0x74,0x7a,0x7e,0x78,0x71,0x73,0x79,0x7d,0x80,0x82,0x86,0x83,0x84,0x80,0x81,0x85,
		0x88,0x8b,0x7f,0x83,0x89,0x8a,0x82,0x79,0x7e,0x7c,0x76,0x74,0x7a,0x79,0x74,0x78,
		0x7e,0x7c,0x75,0x71,0x76,0x7b,0x7e,0x80,0x84,0x84,0x83,0x83,0x7e,0x84,0x85,0x8b,
		0x86,0x7f,0x87,0x89,0x88,0x7d,0x7a,0x7f,0x7a,0x75,0x78,0x7c,0x76,0x75,0x7b,0x7d,
		0x7a,0x72,0x72,0x79,0x7d,0x80,0x82,0x85,0x83,0x84,0x81,0x7f,0x84,0x87,0x8b,0x81,
		0x82,0x87,0x89,0x84,0x7a,0x7d,0x7e,0x77,0x75,0x7b,0x7a,0x75,0x77,0x7d,0x7d,0x77,
		0x71,0x76,0x7a,0x7e,0x80,0x82,0x85,0x83,0x83,0x7e,0x81,0x85,0x89,0x88,0x7e,0x86,
		0x89,0x88,0x7f,0x7a,0x7f,0x7b,0x75,0x77,0x7c,0x77,0x75,0x7a,0x7d,0x7b,0x74,0x72,
		0x78,0x7b,0x7f,0x80,0x85,0x83,0x82,0x81,0x7e,0x83,0x85,0x8b,0x83,0x81,0x88,0x89,
		0x85,0x7b,0x7c,0x7e,0x78,0x75,0x79,0x7b,0x76,0x77,0x7c,0x7d,0x78,0x72,0x75,0x79,
		0x7d,0x80,0x82,0x84,0x82,0x83,0x7f,0x80,0x84,0x88,0x89,0x80,0x84,0x88,0x88,0x80,
		0x7a,0x7f,0x7c,0x77,0x78,0x7c,0x78,0x76,0x78,0x7d,0x7c,0x75,0x72,0x77,0x7b,0x7e,
		0x80,0x83,0x83,0x83,0x81,0x7f,0x82,0x84,0x89,0x85,0x80,0x86,0x88,0x85,0x7d,0x7c,
		0x7e,0x7a,0x76,0x79,0x7b,0x77,0x77,0x7b,0x7d,0x79,0x72,0x74,0x79,0x7c,0x7f,0x81,
		0x83,0x83,0x82,0x80,0x7f,0x83,0x87,0x89,0x80,0x82,0x87,0x88,0x82,0x7b,0x7e,0x7e,
		0x78,0x77,0x7b,0x7a,0x76,0x78,0x7c,0x7c,0x76,0x72,0x77,0x7a,0x7d,0x7f,0x82,0x83,
		0x82,0x82,0x7f,0x82,0x85,0x88,0x86,0x80,0x86,0x88,0x87,0x7e,0x7c,0x7f,0x7c,0x77,
		0x79,0x7b,0x78,0x77,0x7b,0x7d,0x7a,0x74,0x73,0x79,0x7c,0x7f,0x80,0x83,0x82,0x82,
		0x80,0x7f,0x84,0x86,0x89,0x83,0x81,0x86,0x88,0x84,0x7c,0x7d,0x7e,0x79,0x77,0x7b,
		0x7b,0x77,0x78,0x7d,0x7d,0x78,0x73,0x76,0x7a,0x7d,0x80,0x81,0x82,0x82,0x82,0x7f,
		0x81,0x83,0x88,0x86,0x80,0x84,0x87,0x87,0x80,0x7b,0x7e,0x7c,0x77,0x79,0x7c,0x79,
		0x77,0x7b,0x7d,0x7b,0x75,0x74,0x79,0x7b,0x7e,0x80,0x83,0x82,0x82,0x80,0x7e,0x82,
		0x85,0x89,0x84,0x81,0x85,0x87,0x85,0x7d,0x7d,0x7e,0x7b,0x78,0x7b,0x7b,0x77,0x78,
		0x7c,0x7d,0x79,0x74,0x76,0x79,0x7d,0x7f,0x81,0x82,0x82,0x82,0x7f,0x81,0x83,0x87,
		0x87,0x81,0x82,0x86,0x86,0x81,0x7c,0x7e,0x7d,0x79,0x78,0x7c,0x7b,0x77,0x7a,0x7d,
		0x7c,0x77,0x74,0x78,0x7b,0x7e,0x80,0x81,0x83,0x82,0x81,0x7e,0x81,0x84,0x88,0x85,
		0x80,0x85,0x87,0x85,0x7e,0x7c,0x7e,0x7c,0x78,0x79,0x7c,0x78,0x78,0x7b,0x7d,0x7a,
		0x76,0x76,0x79,0x7d,0x7f,0x80,0x83,0x82,0x82,0x80,0x7f,0x82,0x85,0x87,0x80,0x81,
		0x85,0x87,0x83,0x7c,0x7e,0x7d,0x7a,0x78,0x7b,0x7a,0x77,0x7a,0x7c,0x7d,0x78,0x75,
		0x77,0x7c,0x7e,0x7f,0x82,0x83,0x82,0x82,0x7e,0x80,0x83,0x86,0x85,0x7f,0x84,0x86,
		0x86,0x7f,0x7c,0x7e,0x7c,0x78,0x79,0x7d,0x79,0x78,0x7a,0x7e,0x7b,0x80
	};

	buffer = data;
	buffer_size = sizeof(data);
}

#pragma once
#include "../Types.hpp"

namespace Galatea
{
	namespace Audio
	{
		struct WaveFormat
		{
			UInt16 format;                    //Format code
			UInt16 channels;                  //Number of interleaved channels
			UInt32 samples_per_seconds;       //Sampling rate(blocks per second)
			UInt32 average_bytes_per_seconds; //Data rate
			UInt16 block_bytes;               //Data block size(bytes)
			UInt16 bits_per_sample;           //Bits per sample
		};

		class WaveData
		{
			WaveFormat format;
			VoidPtr buffer;
			UInt buffer_size;

			WaveData(const WaveFormat& format, const VoidPtr buffer, UInt buffer_size);

			public:
			WaveData(const WaveData&) = delete;
			WaveData(WaveData&&);
			WaveData& operator=(const WaveData&) = delete;
			WaveData& operator=(WaveData&&);
			~WaveData();

			static WaveData* FromMemory(const VoidPtr buffer, UInt buffer_size);
			static WaveData* FromFile(CStr filename);

			inline const WaveFormat& Format() const { return format; }
			inline const UInt DataByteSize() const { return buffer_size; }
			inline const VoidPtr Data() const { return buffer; }
			inline VoidPtr Data() { return buffer; }

			private:
			WaveData& Move(WaveData&);
			void Destroy();
		};
	}
}

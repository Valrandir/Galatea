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
			Int32 buffer_size;

			WaveData(const WaveFormat& format, const VoidPtr buffer, Int32 buffer_size);

			public:
			WaveData(const WaveData&) = delete;
			WaveData(WaveData&&);
			WaveData& operator=(const WaveData&) = delete;
			WaveData& operator=(WaveData&&);
			~WaveData();

			static WaveData* FromFile(CStr filename);

			inline const WaveFormat& Format() const { return format; }
			inline const Int32 DataByteSize() const { return buffer_size; }
			inline const VoidPtr Data() const { return buffer; }
			inline VoidPtr Data() { return buffer; }

			private:
			WaveData& Move(WaveData&);
			void Destroy();
		};
	}
}

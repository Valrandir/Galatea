#include "WaveData.hpp"
#include "../Assert/Assert.hpp"
#include "../Storage/File.hpp"
using namespace Galatea::Storage;

//http://www-mmsp.ece.mcgill.ca/documents/AudioFormats/WAVE/WAVE.html

namespace Galatea
{
	namespace Audio
	{
		const UInt32 LITTLE_ENDIAN_RIFF_TAG = 0x46464952;
		const UInt32 LITTLE_ENDIAN_FMT_TAG = 0x20746d66;
		const UInt32 LITTLE_ENDIAN_DATA_TAG = 0x61746164;

		struct Chunk
		{
			char chunk_id[4];
			UInt32 chunk_size;
		};

		struct RiffChunk
		{
			Chunk chunk;
			char wave_id[4];
		};

		struct FmtChunk
		{
			Chunk chunk;
			WaveFormat format;
		};

		WaveData::WaveData(const WaveFormat& format, const VoidPtr buffer, Int32 buffer_size) : format{format}, buffer_size{buffer_size}
		{
			this->buffer = Memory::Alloc(buffer_size);
			Memory::Copy(buffer, this->buffer, buffer_size);
		}

		WaveData::WaveData(WaveData&& src) : buffer{}
		{
			Move(src);
		}

		WaveData& WaveData::operator=(WaveData&& src)
		{
			return Move(src);
		}

		WaveData::~WaveData()
		{
			Destroy();
		}

		WaveData* WaveData::FromFile(CStr filename)
		{
			File* file;
			ASSERT(file = File::Open(filename, File::Disposition::OpenExisting, File::Access::AccessRead, File::Flags::ShareRead));

			auto buffer_size = file->GetFileSize();
			auto buffer = Memory::Alloc(buffer_size);

			ASSERT(file->Read(buffer, buffer_size));
			delete file;

			const UInt32 LITTLE_ENDIAN_RIFF_TAG = 0x46464952;
			const UInt32 LITTLE_ENDIAN_FMT_TAG = 0x20746d66;
			const UInt16 WAVE_FORMAT_PCM = 0x1;

			RiffChunk* riff_chunk;
			FmtChunk* fmt_chunk;
			Chunk* data_chunk;

			auto it = reinterpret_cast<UInt8*>(buffer);
			riff_chunk = reinterpret_cast<RiffChunk*>(it);

			bool ok;
			ok = *reinterpret_cast<UInt32*>(riff_chunk->chunk.chunk_id) == LITTLE_ENDIAN_RIFF_TAG;

			if(ok)
			{
				it += sizeof(RiffChunk);
				fmt_chunk = reinterpret_cast<FmtChunk*>(it);
				ok = *reinterpret_cast<Int32*>(fmt_chunk->chunk.chunk_id) == LITTLE_ENDIAN_FMT_TAG;
			}

			if(ok)
				ok = fmt_chunk->chunk.chunk_size == 16 && fmt_chunk->format.format == WAVE_FORMAT_PCM;

			if(ok)
			{
				it += sizeof(Chunk) + fmt_chunk->chunk.chunk_size;
				data_chunk = reinterpret_cast<Chunk*>(it);
				ok = *reinterpret_cast<Int32*>(data_chunk->chunk_id) == LITTLE_ENDIAN_DATA_TAG;
			}

			WaveData* waveData = nullptr;

			if(ok)
				waveData = new WaveData(fmt_chunk->format, data_chunk + sizeof(Chunk), data_chunk->chunk_size);

			Memory::Free(buffer);
			return waveData;
		}

		WaveData& WaveData::Move(WaveData& src)
		{
			Destroy();
			buffer = src.buffer;
			buffer_size = src.buffer_size;
			src.buffer = nullptr;
			src.buffer_size = 0;
			return *this;
		}

		void WaveData::Destroy()
		{
			if(buffer)
			{
				Memory::Free(buffer);
				buffer = nullptr;
				buffer_size = 0;
			}
		}
	}
}

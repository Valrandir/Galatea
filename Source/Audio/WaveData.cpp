#include "WaveData.hpp"
#include "../Assert/Assert.hpp"
#include "../Storage/File.hpp"
using namespace Galatea::Storage;

//http://www-mmsp.ece.mcgill.ca/documents/AudioFormats/WAVE/WAVE.html

namespace Galatea
{
	namespace Audio
	{
		static const UInt32 LITTLE_ENDIAN_RIFF_TAG = 0x46464952;
		static const UInt32 LITTLE_ENDIAN_WAVE_TAG = 0x45564157;
		static const UInt32 LITTLE_ENDIAN_FMT_TAG = 0x20746d66;
		static const UInt32 LITTLE_ENDIAN_DATA_TAG = 0x61746164;
		static const UInt16 WAVE_FORMAT_PCM = 0x1;

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

		WaveData::WaveData(const WaveFormat& format, const VoidPtr buffer, UInt buffer_size) : format{format}, buffer_size{buffer_size}
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

		WaveData* WaveData::FromMemory(const VoidPtr buffer, UInt buffer_size)
		{
			auto it = reinterpret_cast<UInt8*>(buffer);
			auto end = it + buffer_size;

			auto chunk = reinterpret_cast<Chunk*>(it);

			if(*reinterpret_cast<UInt32*>(chunk->chunk_id) != LITTLE_ENDIAN_RIFF_TAG)
				return nullptr;

			auto riff = reinterpret_cast<RiffChunk*>(it);
			if(*reinterpret_cast<UInt32*>(riff->wave_id) != LITTLE_ENDIAN_WAVE_TAG)
				return nullptr;

			it += sizeof(RiffChunk);

			FmtChunk* fmt_chunk = nullptr;
			Chunk* data_chunk = nullptr;

			while(it < end - sizeof(Chunk) && (!fmt_chunk || !data_chunk))
			{
				chunk = reinterpret_cast<Chunk*>(it);

				switch(*reinterpret_cast<UInt32*>(chunk->chunk_id))
				{
					case LITTLE_ENDIAN_FMT_TAG:
						fmt_chunk = reinterpret_cast<FmtChunk*>(it);
						if(fmt_chunk->format.format != WAVE_FORMAT_PCM)
							return nullptr;
						break;
					case LITTLE_ENDIAN_DATA_TAG:
						data_chunk = reinterpret_cast<Chunk*>(it);
						break;
				}

				it += sizeof(Chunk) + chunk->chunk_size;
			}

			if(fmt_chunk && data_chunk)
				return new WaveData(fmt_chunk->format, data_chunk + sizeof(Chunk), data_chunk->chunk_size);

			return nullptr;
		}

		WaveData* WaveData::FromFile(CStr filename)
		{
			File* file;
			ASSERT(file = File::Open(filename, File::Disposition::OpenExisting, File::Access::AccessRead, File::Flags::ShareRead));

			auto buffer_size = file->GetFileSize();
			auto buffer = Memory::Alloc(buffer_size);

			ASSERT(file->Read(buffer, buffer_size));
			delete file;

			return FromMemory(buffer, buffer_size);
			Memory::Free(buffer);
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

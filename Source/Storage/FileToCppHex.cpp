#include "../Assert/Assert.hpp"
#include "../Storage/Storage.hpp"

namespace Galatea
{
	namespace Storage
	{
		using namespace Galatea;
		using namespace Storage;

		void FileToCppHex(const wchar_t* source_png_file, const wchar_t* target_cpp_file)
		{
			File* file;
			ASSERT(file = File::Open(source_png_file, File::Disposition::OpenExisting, File::Access::AccessRead, 0));

			UInt size = ToUInt(file->GetFileSize());
			VoidPtr buffer = Memory::Alloc(size);
			file->Read(buffer, size);
			delete file;

			TextFile* out;
			ASSERT_SYSTEMCALL(out = TextFile::Create(target_cpp_file));

			const UInt s_buffer_size = 10;
			TChar s_buffer[s_buffer_size];
			UInt8* it = reinterpret_cast<UInt8*>(buffer);
			UInt8* end = it + size;

			out->WriteLine(L"const UInt8 file_data[] =");
			out->WriteLine(L"{");
			out->Write(L"\t");

			int line_count = 0;
			while(it < end)
			{
				String::FormatToBuffer(s_buffer, s_buffer_size, it < end - 1 ? L"0x%02x," : L"0x%02x", *it);
				out->Write(s_buffer);
				++it;

				if(++line_count % 16 == 0)
				{
					out->WriteLine(L"");
					out->Write(L"\t");
				}
			}

			out->WriteLine(L"");
			out->WriteLine(L"};");

			delete out;
		}
	}
}

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Galatea
{
	namespace Text
	{
		//Must delete the returned pointer when done
		const char* WideToAnsii(const wchar_t* source)
		{
			int byte_size = WideCharToMultiByte(CP_UTF8, 0, source, -1, nullptr, 0, 0, nullptr);
			char* buffer = new char[byte_size];
			WideCharToMultiByte(CP_UTF8, 0, source, -1, buffer, byte_size, 0, nullptr);
			return buffer;
		}

		//Must delete the returned pointer when done
		const char* WideToAnsii(const char* source)
		{
			const size_t byte_size = strlen(source);
			char* buffer = new char[byte_size];
			for(size_t i = 0; i < byte_size; ++i)
				buffer[i] = source[i];
			return buffer;
		}
	}
}

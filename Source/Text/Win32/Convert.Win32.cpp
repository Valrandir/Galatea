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
			const size_t byte_size = strlen(source) * sizeof(char);
			char* buffer = new char[byte_size];
			for(size_t i = 0; i < byte_size; ++i)
				buffer[i] = source[i];
			return buffer;
		}

		//Must delete the returned pointer when done
		const wchar_t* AnsiiToWide(const char* source)
		{
			int byte_size = MultiByteToWideChar(CP_UTF8, 0, source, -1, nullptr, 0);
			wchar_t* buffer = new wchar_t[byte_size];
			MultiByteToWideChar(CP_UTF8, 0, source, -1, buffer, byte_size);
			return buffer;
		}

		//Must delete the returned pointer when done
		const wchar_t* AnsiiToWide(const wchar_t* source)
		{
			const size_t byte_size = wcslen(source) * sizeof(wchar_t);
			wchar_t* buffer = new wchar_t[byte_size];
			for(size_t i = 0; i < byte_size; ++i)
				buffer[i] = source[i];
			return buffer;
		}
	}
}

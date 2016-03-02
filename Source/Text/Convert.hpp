#pragma once
#include "../Types.hpp"

namespace Galatea
{
	namespace Text
	{
		//Must delete the returned pointer when done
		const char* WideToAnsii(const wchar_t* source);

		//Must delete the returned pointer when done
		const char* WideToAnsii(const char* source);
	}
}

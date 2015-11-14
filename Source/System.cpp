#include "System.hpp"

#define BUFFER_SIZE 0x200U

namespace Core
{
	String GetErrText(UInt32 errCode)
	{
		TChar buffer[BUFFER_SIZE];
		CStr msg = GetErrText(errCode, buffer, BUFFER_SIZE);
		return String(msg);
	}
}

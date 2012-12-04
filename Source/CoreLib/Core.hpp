#pragma once

#if !defined(CoreTargetWin32) && !defined(CoreTargetLinux)
	#error Define either CoreTargetWin32 or CoreTargetLinux
#endif

#include "Types.hpp"
#include "System/System.hpp"
#include "System/Memory/Memory.hpp"
#include "System/Threading/IThread.hpp"
#include "System/Time/Time.hpp"

#pragma once

#if !CoreTargetWin32 && !CoreTargetLinux
	#error No target defined.
#endif

#include "Types.hpp"

#include "System.hpp"
#include "Memory/Memory.hpp"
#include "Threading/Thread.hpp"
#include "Time/Time.hpp"

#include "Assert/Assert.hpp"
#include "DataStruct/Vector.hpp"
#include "String/String.hpp"
#include "Storage/File.hpp"
#include "Storage/TextFile.hpp"

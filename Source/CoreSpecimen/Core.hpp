#pragma once
#include <Core.hpp>

#define ASSERT result = result && 

#ifdef CoreTargetLinux
	#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
	#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

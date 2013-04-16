#pragma once
#include <Core.hpp>

#define CHECK result = result && 
#define CHECK_ASSERT(func) \
	if(result) \
		try { func; result = false; } \
		catch(CoreException const &) { Assert::Failing = false; result = true; }

#ifdef CoreTargetLinux
	#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
	#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

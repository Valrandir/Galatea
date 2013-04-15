#pragma once
#include <Core.hpp>

#define CHECK result = result && 
#define CHECK_ASSERT(func) \
	try { func; result = false; } \
	catch(CoreException const &) { result = true; }

#ifdef CoreTargetLinux
	#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
	#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

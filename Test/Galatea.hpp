#pragma once
#include "../Include/Galatea.hpp"

#define CHECK result = result && 
#define CHECK_ASSERT(func) \
	if(result) \
		try { func; result = false; } \
		catch(Exception const &) { Assert::Failing = false; result = true; }

#ifdef CoreTargetLinux
	#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
	#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

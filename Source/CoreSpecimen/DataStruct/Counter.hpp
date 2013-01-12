#pragma once
#include "../Core.hpp"
using namespace Core;

struct Counter
{
	UInt ID;
	static UInt IDIncrement;
	static UInt Construct;
	static UInt CopyConstruct;
	static UInt OperatorEqual;
	static UInt Destruct;

	Counter();
	Counter(Counter const & Source);
	Counter& operator=(Counter const & Source);
	~Counter();

	static Bool Assert(UInt Construct, UInt CopyConstruct, UInt OperatorEqual, UInt Destruct);
	static void Clear();
};

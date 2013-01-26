#pragma once
#include "../Core.hpp"
using namespace Core;

struct Counter
{
	UInt ID;
	static UInt IDIncrement;
	static UInt Construct;
	static UInt CopyConstruct;
	static UInt MoveConstruct;
	static UInt OperatorEqual;
	static UInt OperatorMove;
	static UInt Destruct;

	Counter();
	Counter(Counter const & Source);
	Counter(Counter const && Source);
	Counter& operator=(Counter const & Source);
	Counter& operator=(Counter const && Source);
	~Counter();

	static Bool Counter::Assert(UInt Construct, UInt CopyConstruct, UInt MoveConstruct, UInt OperatorEqual, UInt OperatorMove, UInt Destruct);
	static void Clear();
};

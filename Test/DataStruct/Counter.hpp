#pragma once
#include "../Galatea.hpp"
using namespace Galatea;

struct Counter
{
	UInt _id;
	static UInt _idIncrement;
	static UInt _construct;
	static UInt _copyConstruct;
	static UInt _moveConstruct;
	static UInt _operatorEqual;
	static UInt _operatorMove;
	static UInt _destruct;

	Counter();
	Counter(Counter const & source);
	Counter(Counter const && source);
	Counter& operator=(Counter const & source);
	Counter& operator=(Counter const && source);
	~Counter();

	static Bool Compare(UInt construct, UInt copyConstruct, UInt moveConstruct, UInt operatorEqual, UInt operatorMove, UInt destruct);
	static void Clear();
};

#include "Counter.hpp"

UInt Counter::IDIncrement = 0U;
UInt Counter::Construct = 0U;
UInt Counter::CopyConstruct = 0U;
UInt Counter::OperatorEqual = 0U;
UInt Counter::Destruct = 0U;

Counter::Counter()
{
	++Construct;
	++IDIncrement;
	ID = IDIncrement;
}

Counter::Counter(Counter const & Source)
{
	++CopyConstruct;
	ID = Source.ID;
}

Counter& Counter::operator=(Counter const & Source)
{
	++OperatorEqual;
	ID = Source.ID;
	return *this;
}

Counter::~Counter()
{
	++Destruct;
}

Bool Counter::Assert(UInt Construct, UInt CopyConstruct, UInt OperatorEqual, UInt Destruct)
{
	return
		Counter::Construct == Construct &&
		Counter::CopyConstruct == CopyConstruct &&
		Counter::OperatorEqual == OperatorEqual &&
		Counter::Destruct == Destruct;
}

void Counter::Clear()
{
	IDIncrement = 0U;
	Construct = 0U;
	CopyConstruct = 0U;
	OperatorEqual = 0U;
	Destruct = 0U;
}

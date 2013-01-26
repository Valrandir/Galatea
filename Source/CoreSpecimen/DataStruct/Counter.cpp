#include "Counter.hpp"

UInt Counter::IDIncrement = 0U;
UInt Counter::Construct = 0U;
UInt Counter::CopyConstruct = 0U;
UInt Counter::MoveConstruct = 0U;
UInt Counter::OperatorEqual = 0U;
UInt Counter::OperatorMove = 0U;
UInt Counter::Destruct = 0U;

//Constructor
Counter::Counter()
{
	++Construct;
	++IDIncrement;
	ID = IDIncrement;
}

//Copy Constructor
Counter::Counter(Counter const & Source)
{
	++CopyConstruct;
	ID = Source.ID;
}

//Move Constructor
Counter::Counter(Counter const && Source)
{
	++MoveConstruct;
	ID = Source.ID;
}

//Assignment Operator
Counter& Counter::operator=(Counter const & Source)
{
	++OperatorEqual;
	ID = Source.ID;
	return *this;
}

//Move Assignment Operator
Counter& Counter::operator=(Counter const && Source)
{
	++OperatorMove;
	ID = Source.ID;
	return *this;
}

//Destructor
Counter::~Counter()
{
	++Destruct;
}

Bool Counter::Assert(UInt Construct, UInt CopyConstruct, UInt MoveConstruct, UInt OperatorEqual, UInt OperatorMove, UInt Destruct)
{
	return
		Counter::Construct == Construct &&
		Counter::CopyConstruct == CopyConstruct &&
		Counter::MoveConstruct == MoveConstruct &&
		Counter::OperatorEqual == OperatorEqual &&
		Counter::OperatorMove == OperatorMove &&
		Counter::Destruct == Destruct;
}

void Counter::Clear()
{
	IDIncrement = 0U;
	Construct = 0U;
	CopyConstruct = 0U;
	MoveConstruct = 0U;
	OperatorEqual = 0U;
	OperatorMove = 0U;
	Destruct = 0U;
}

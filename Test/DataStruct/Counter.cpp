#include "Counter.hpp"

UInt Counter::_idIncrement = 0U;
UInt Counter::_construct = 0U;
UInt Counter::_copyConstruct = 0U;
UInt Counter::_moveConstruct = 0U;
UInt Counter::_operatorEqual = 0U;
UInt Counter::_operatorMove = 0U;
UInt Counter::_destruct = 0U;

//Constructor
Counter::Counter()
{
	++_construct;
	++_idIncrement;
	_id = _idIncrement;
}

//Copy Constructor
Counter::Counter(Counter const & source)
{
	++_copyConstruct;
	_id = source._id;
}

//Move Constructor
Counter::Counter(Counter const && source)
{
	++_moveConstruct;
	_id = source._id;
}

//Assignment Operator
Counter& Counter::operator=(Counter const & source)
{
	++_operatorEqual;
	_id = source._id;
	return *this;
}

//Move Assignment Operator
Counter& Counter::operator=(Counter const && source)
{
	++_operatorMove;
	_id = source._id;
	return *this;
}

//Destructor
Counter::~Counter()
{
	++_destruct;
}

Bool Counter::Compare(UInt construct, UInt copyConstruct, UInt moveConstruct, UInt operatorEqual, UInt operatorMove, UInt destruct)
{
	return
		Counter::_construct == construct &&
		Counter::_copyConstruct == copyConstruct &&
		Counter::_moveConstruct == moveConstruct &&
		Counter::_operatorEqual == operatorEqual &&
		Counter::_operatorMove == operatorMove &&
		Counter::_destruct == destruct;
}

void Counter::Clear()
{
	_idIncrement = 0U;
	_construct = 0U;
	_copyConstruct = 0U;
	_moveConstruct = 0U;
	_operatorEqual = 0U;
	_operatorMove = 0U;
	_destruct = 0U;
}

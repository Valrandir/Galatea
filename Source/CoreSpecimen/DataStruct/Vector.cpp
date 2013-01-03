#include "../Core.hpp"
using namespace Core;
using namespace DataStruct;

void AddTest()
{
	Vector<Int> VectorInt;
	UInt Capacity;
	UInt Length;

	Capacity = VectorInt.GetCapacity();
	Length = VectorInt.GetLength();

	VectorInt.Add(5);
	VectorInt.Add(35);
	VectorInt.Add(68);
	VectorInt.Add(15);
}

void RemoveTest()
{
	Vector<Int> VectorInt;
	UInt Capacity;
	UInt Length;

	Capacity = VectorInt.GetCapacity();
	Length = VectorInt.GetLength();

	VectorInt.Add(5);
	VectorInt.Add(35);
	VectorInt.Add(68);
	VectorInt.Add(15);
	VectorInt.Add(578);

	VectorInt.Remove(100);
	VectorInt.Remove(4);
	VectorInt.Remove(0);
	VectorInt.Remove(1);
}

void ReserveTest()
{
	Vector<Int> VectorInt;
	UInt Capacity;
	UInt Length;

	Capacity = VectorInt.GetCapacity();
	Length = VectorInt.GetLength();

	VectorInt.Reserve(500U);

	VectorInt.Add(5);
	VectorInt.Add(35);
	VectorInt.Add(68);
	VectorInt.Add(15);
}

void IteratorTest()
{
	Vector<Int> VectorInt;
	Int Value;

	VectorInt.Add(5);
	VectorInt.Add(35);

	for(auto it = VectorInt.Begin(); it < VectorInt.End(); ++it)
	{
		*it = *it;
		Value = *it;
	}

	for(auto it = VectorInt.CBegin(); it < VectorInt.CEnd(); ++it)
	{
		//*it = *it;
		Value = *it;
	}
}

void ClearTest()
{
	class LoL
	{
		public:
		LoL()
		{
			int x = 0;
			int y = 0;
			int z = x + y;
		}

		LoL(LoL const &)
		{
			int x = 0;
			int y = 0;
			int z = x + y;
		}

		~LoL()
		{
			int x = 0;
			int y = 0;
			int z = x + y;
		}
	};

	Vector<LoL> VectorInt;
	VectorInt.Add(LoL());
}

void InsertTest()
{
	Vector<Int> VectorInt;

	VectorInt.Insert(1000, 5);
	VectorInt.Add(35);
	VectorInt.Add(68);

	VectorInt.Insert(0, 100);
	VectorInt.Insert(3, 200);
	VectorInt.Insert(2, 300);
}

void VectorTest()
{
	AddTest();
	RemoveTest();
	ReserveTest();
	IteratorTest();
	ClearTest();
	InsertTest();
}

#pragma once
#include "../Types.hpp"
#include "../System/Memory/Memory.hpp"

namespace Core
{
	namespace DataStruct
	{
		template<class ItemType> class Vector
		{
			ItemType* VecPtr;
			UInt Capacity;
			UInt Length;

			void AllocSpace();
			void DestroyAll();

			public:
			typedef ItemType* Iterator;
			typedef ItemType const * ConstIterator;

			Vector();
			~Vector();

			void Reserve(UInt Capacity);

			void Add(ItemType const & Value);
			void Insert(UInt Position, ItemType const & Value);
			void Remove(UInt Position);

			void Clear();
			void Free();

			UInt GetCapacity() const;
			UInt GetLength() const;

			ItemType operator[](UInt Position) const;

			Iterator Begin();
			Iterator End();
			ConstIterator Begin() const;
			ConstIterator End() const;
			ConstIterator CBegin() const;
			ConstIterator CEnd() const;
		};

		#include "Vector.cpp"
	}
}

#pragma once
#include "../Types.hpp"
#include "../System/Memory/Memory.hpp"

//Placement New
inline Core::VoidPtr operator new(Core::UInt, Core::VoidPtr Address)
{
	return Address;
}

namespace Core
{
	namespace DataStruct
	{
		template<class T> class Vector
		{
			T* VecPtr;
			UInt Capacity;
			UInt Length;

			private:
			void Allocate(UInt Capacity);
			void AutoAllocate();
			void Construct(T const * Element, T const & Source) const;
			void Destroy(T const * Element) const;
			void Destroy(T const * Begin, T const * End) const;
			void Copy(T* Target, T const * Begin, T const * End) const;
			void InitializeFromVector(Vector const & Source);

			public:
			typedef T* Iterator;
			typedef T const * ConstIterator;

			Vector();
			Vector(UInt Capacity);
			Vector(Vector const & Source);
			Vector& operator=(Vector const & Source);
			~Vector();

			void Reserve(UInt Capacity);
			void Shrink();
			void Clear();
			void Free();

			void Add(T const & Value);
			void Insert(UInt Position, T const & Value);
			void Remove(UInt Position);

			T& operator[](UInt Position);
			T const & operator[](UInt Position) const;

			UInt GetCapacity() const;
			UInt GetLength() const;

			Iterator Begin();
			Iterator End();
			ConstIterator Begin() const;
			ConstIterator End() const;
		};

		#include "Vector.cpp"
	}
}

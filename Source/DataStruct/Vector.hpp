/* Vector.hpp */

#pragma once
#include "../Types.hpp"
#include "../Memory/Memory.hpp"
#include "VectorAssert.hpp"

//Added this instead of the manual placement new/delete definition, otherwise Vector and std::vector conflicted.
//This is the better way anyways.
//Also Vector is definetly not as good as std::vector, which should be used instead.
#include <new>

namespace Galatea
{
	namespace DataStruct
	{
		template<class T> class Vector
		{
			public:
			enum CtorMode{Always, Once, Pod};
			typedef T Element;
			typedef T const ConstElement;

			//DefaultMode is private except for UnitTest
			#ifndef VectorUnitTest
				private:
			#endif
			static CtorMode DefaultMode;

			private:
			CtorMode _ctorMode;
			Element* _origin; //Array Start
			Element* _last; //Sequence End
			Element* _end; //Array End

			/* Private Functions */
			void Deallocate();
			void Allocate(UInt capacity);
			void AutoAllocate();
			void Construct(ConstElement* target, ConstElement* source) const;
			void Move(ConstElement* target, Element *source) const;
			void Destroy(ConstElement* target) const;
			void Destroy(ConstElement* begin, ConstElement* end) const;
			void MoveRange(Element* target, Element* begin, Element* end) const;
			void CopyToSelf(Vector const & source);
			void MoveToSelf(Vector & source);

			public:
			/* Constructors && Destructor */
			Vector(CtorMode ctorMode = DefaultMode);
			Vector(UInt capacity, CtorMode ctorMode = DefaultMode);
			Vector(ConstElement* begin, ConstElement* end, CtorMode ctorMode = DefaultMode);
			Vector(Vector const & source);
			Vector(Vector&& Source);
			virtual ~Vector();

			/* Operators */
			Vector& operator=(Vector const & source);
			Vector& operator=(Vector&& source);
			Vector& operator+=(Vector const & source);
			Element& operator[](UInt offset);
			ConstElement& operator[](UInt offset) const;

			/* Accesors */
			CtorMode GetCtorMode() const;
			Bool IsEmpty() const;
			UInt Capacity() const;
			UInt Length() const;

			/* Iterators */
			Element* Begin();
			Element* End();
			Element* RBegin();
			Element* REnd();
			ConstElement* Begin() const;
			ConstElement* End() const;
			ConstElement* RBegin() const;
			ConstElement* REnd() const;

			/* Public Functions */
			void Reserve(UInt capacity);
			void Shrink();
			void Clear();
			void Free();
			void Add(ConstElement& value);
			void AddRange(ConstElement* begin, ConstElement* end);
			void Insert(Element& at, ConstElement& value);
			void Insert(UInt offset, ConstElement& value);
			void Remove(Element& item);
			void Remove(UInt position);
			Element* DrivePointer(UInt future_length);
		};

		#include "Vector.tpp"
	}
}

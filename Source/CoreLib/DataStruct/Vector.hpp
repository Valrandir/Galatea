/* Vector.hpp */

#pragma once
#include "../Types.hpp"
#include "../System/Assert/Assert.hpp"
#include "../System/Memory/Memory.hpp"

//Placement New
#ifdef CoreTargetWin32
	inline void* operator new(Core::UInt, void* address){return address;}
	inline void operator delete(void*, void*){}
#elif CoreTargetLinux
	#ifdef CoreTarget64Bits
		inline void* operator new(long unsigned int, void* address){return address;}
	#else
		inline void* operator new(unsigned int, void* address){return address;}
	#endif
	inline void operator delete(void*, void*){}
#endif

namespace Core
{
	namespace DataStruct
	{
		template<class T> class Vector
		{
			public:
			enum CtorModeEnum{Always, Once, Pod};
			typedef T Element;
			typedef T const ConstElement;

			//DefaultMode is private except for UnitTest
			#ifndef VectorUnitTest
				private:
			#endif
			static CtorModeEnum DefaultMode;

			private:
			CtorModeEnum _ctorMode;
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
			Vector(CtorModeEnum ctorMode = DefaultMode);
			Vector(UInt capacity, CtorModeEnum ctorMode = DefaultMode);
			Vector(ConstElement* begin, ConstElement* end, CtorModeEnum ctorMode = DefaultMode);
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
			CtorModeEnum GetElementType() const;
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

		#include "Vector.cpp"
	}
}

template <class ItemType> void Vector<ItemType>::AllocSpace()
{
	if(Capacity == 0U)
		Reserve(2U);
	else if(Capacity == Length)
		Reserve(Capacity << 1U);
}

template <class ItemType> void Vector<ItemType>::DestroyAll()
{
	Iterator it = Begin();
	Iterator end = End();
	while(it < end)
		it++->~ItemType();
}

template<class ItemType> Vector<ItemType>::Vector() : VecPtr(NULL), Capacity(0U), Length(0U) {}

template<class ItemType> Vector<ItemType>::~Vector()
{
	Reset();
}

template<class ItemType> void Vector<ItemType>::Reserve(UInt Capacity)
{
	ItemType* ptr;

	if(Capacity > this->Capacity)
	{
		ptr = (ItemType*)System::Memory::Alloc(sizeof(ItemType) * Capacity);
		if(VecPtr)
		{
			System::Memory::Copy(VecPtr, ptr, sizeof(ItemType) * this->Capacity);
			System::Memory::Free(VecPtr);
		}
		VecPtr = ptr;
		this->Capacity = Capacity;
	}
}

template<class ItemType> void Vector<ItemType>::Add(ItemType const & Value)
{
	Insert(Length, Value);
}

template<class ItemType> void Vector<ItemType>::Insert(UInt Position, ItemType const & Value)
{
	ItemType* ptr;
	Bool insert;

	AllocSpace();

	//If Position is beyond the end then insert at end.
	insert = Position < Length;
	ptr = insert ? VecPtr + Position : VecPtr + Length;

	if(insert)
		System::Memory::Move(ptr, ptr + 1, sizeof(ItemType) * (Length - Position));

	new((VoidPtr)ptr) ItemType(Value);
	++Length;
}

template<class ItemType> void Vector<ItemType>::Remove(UInt Position)
{
	ItemType* ptr;

	if(Position < Length)
	{
		--Length;
		ptr = VecPtr + Position;
		ptr->~ItemType();
		System::Memory::Move(ptr + 1, ptr, sizeof(ItemType) * (Length - Position));
	}
}

template<class ItemType> void Vector<ItemType>::Clear()
{
	DestroyAll();
	Length = 0U;
}

template<class ItemType> void Vector<ItemType>::Reset()
{
	if(VecPtr)
	{
		DestroyAll();
		System::Memory::Free(VecPtr);
		VecPtr = NULL;
		Capacity = 0U;
		Length = 0U;
	}
}

template<class ItemType> UInt Vector<ItemType>::GetCapacity() const
{
	return Capacity;
}

template<class ItemType> UInt Vector<ItemType>::GetLength() const
{
	return Length;
}

template<class ItemType> ItemType Vector<ItemType>::operator[](UInt Position) const
{
	return *(VecPtr + Position);
}

template<class ItemType> typename Vector<ItemType>::Iterator Vector<ItemType>::Begin()
{
	return VecPtr;
}

template<class ItemType> typename Vector<ItemType>::Iterator Vector<ItemType>::End()
{
	return VecPtr + Length;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::Begin() const
{
	return VecPtr;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::End() const
{
	return VecPtr + Length;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::CBegin() const
{
	return VecPtr;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::CEnd() const
{
	return VecPtr + Length;
}

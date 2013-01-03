template <class ItemType> void Vector<ItemType>::AssumeFreeSpace()
{
	if(Capacity == 0U)
		Reserve(2U);
	else if(Capacity == Length)
		Reserve(Capacity << 1U);
}

template<class ItemType> Vector<ItemType>::Vector() : Ptr(NULL), Capacity(0U), Length(0U) {}

template<class ItemType> Vector<ItemType>::~Vector()
{
	Reset();
}

template<class ItemType> void Vector<ItemType>::Reserve(UInt Capacity)
{
	ItemType* NewPtr;

	if(Capacity > this->Capacity)
	{
		NewPtr = (ItemType*)System::Memory::Alloc(sizeof(ItemType) * Capacity);
		if(Ptr)
		{
			System::Memory::Copy(Ptr, NewPtr, sizeof(ItemType) * this->Capacity);
			System::Memory::Free(Ptr);
		}
		Ptr = NewPtr;
		this->Capacity = Capacity;
	}
}

template<class ItemType> void Vector<ItemType>::Add(ItemType Value)
{
	AssumeFreeSpace();
	*(Ptr + Length) = Value;
	++Length;
}

template<class ItemType> void Vector<ItemType>::Insert(UInt Position, ItemType Value)
{
	ItemType* Ptr;

	AssumeFreeSpace();

	if(Position >= Length)
	{
		*(this->Ptr + Length) = Value;
		++Length;
	}
	else
	{
		Ptr = this->Ptr + Position;
		System::Memory::Move(Ptr, Ptr + 1, sizeof(ItemType) * (Length - Position));
		*Ptr = Value;
		++Length;
	}
}

template<class ItemType> void Vector<ItemType>::Remove(UInt Position)
{
	ItemType* Ptr;

	if(Position < Length)
	{
		--Length;
		Ptr = this->Ptr + Position;
		Ptr->~ItemType();
		System::Memory::Move(Ptr + 1, Ptr, sizeof(ItemType) * (Length - Position));
	}
}

template<class ItemType> void Vector<ItemType>::Clear()
{
	Iterator it, end;

	if(Ptr)
	{
		for(it = Begin(), end = End(); it < end; ++it)
			it->~ItemType();

		Length = 0U;
	}
}

template<class ItemType> void Vector<ItemType>::Reset()
{
	Iterator it, end;

	if(Ptr)
	{
		for(it = Begin(), end = End(); it < end; ++it)
			it->~ItemType();

		System::Memory::Free(Ptr);
		Ptr = NULL;
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
	return *(Ptr + Position);
}

template<class ItemType> typename Vector<ItemType>::Iterator Vector<ItemType>::Begin()
{
	return Ptr;
}

template<class ItemType> typename Vector<ItemType>::Iterator Vector<ItemType>::End()
{
	return Ptr + Length + 1;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::Begin() const
{
	return Ptr;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::End() const
{
	return Ptr + Length + 1;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::CBegin() const
{
	return Ptr;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::CEnd() const
{
	return Ptr + Length + 1;
}

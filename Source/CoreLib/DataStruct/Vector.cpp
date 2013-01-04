template <class ItemType> void Vector<ItemType>::AssumeFreeSpace()
{
	if(Capacity == 0U)
		Reserve(2U);
	else if(Capacity == Length)
		Reserve(Capacity << 1U);
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

template<class ItemType> void Vector<ItemType>::Add(ItemType Value)
{
	AssumeFreeSpace();
	*(VecPtr + Length) = Value;
	++Length;
}

template<class ItemType> void Vector<ItemType>::Insert(UInt Position, ItemType Value)
{
	ItemType* ptr;

	AssumeFreeSpace();

	if(Position >= Length)
	{
		*(VecPtr + Length) = Value;
		++Length;
	}
	else
	{
		ptr = VecPtr + Position;
		System::Memory::Move(ptr, ptr + 1, sizeof(ItemType) * (Length - Position));
		*ptr = Value;
		++Length;
	}
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
	Iterator it, end;

	if(VecPtr)
	{
		for(it = Begin(), end = End(); it < end; ++it)
			it->~ItemType();

		Length = 0U;
	}
}

template<class ItemType> void Vector<ItemType>::Reset()
{
	Iterator it, end;

	if(VecPtr)
	{
		for(it = Begin(), end = End(); it < end; ++it)
			it->~ItemType();

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
	return VecPtr + Length + 1;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::Begin() const
{
	return VecPtr;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::End() const
{
	return VecPtr + Length + 1;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::CBegin() const
{
	return VecPtr;
}

template<class ItemType> typename Vector<ItemType>::ConstIterator Vector<ItemType>::CEnd() const
{
	return VecPtr + Length + 1;
}

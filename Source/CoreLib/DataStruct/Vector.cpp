
template<class T> void Vector<T>::Allocate(UInt Capacity)
{
	T* VecPtr;
	UInt Length;

	VecPtr = (T*)System::Memory::Alloc(sizeof(T) * Capacity);
	if(this->VecPtr)
		Copy(VecPtr, Begin(), End());
	Length = this->Length;
	Free();

	this->VecPtr = VecPtr ;
	this->Capacity = Capacity;
	this->Length = Length;
}

template <class T> void Vector<T>::AutoAllocate()
{
	if(Capacity == 0U)
		Allocate(2U);
	else if(Capacity == Length)
		Allocate(Capacity << 1U);
}

template <class T> void Vector<T>::Construct(T const * Element, T const & Source) const
{
	new((VoidPtr)Element) T(Source);
}

template <class T> void Vector<T>::Destroy(ConstIterator Element) const
{
	Element->~T();
}

template <class T> void Vector<T>::Destroy(ConstIterator Begin, ConstIterator End) const
{
	for(ConstIterator Iterator = Begin; Iterator < End; ++Iterator)
		Destroy(Iterator);
}

template <class T> void Vector<T>::Copy(T* Target, T const * Begin, T const * End) const
{
	if(Target)
		for(ConstIterator Iterator = Begin; Iterator < End; ++Target, ++Iterator)
			Construct(Target, *Iterator);
}

template <class T> void Vector<T>::InitializeFromVector(Vector const & Source)
{
	Length = Source.Length;
	Allocate(Length);
	Copy(VecPtr, Source.Begin(), Source.End());
}

template<class T> Vector<T>::Vector() : VecPtr(NULL), Capacity(0U), Length(0U) {}

template<class T> Vector<T>::Vector(UInt Capacity) : VecPtr(NULL), Capacity(0U), Length(0U)
{
	Allocate(Capacity);
}

template<class T> Vector<T>::Vector(Vector const & Source) : VecPtr(NULL), Capacity(0U), Length(0U)
{
	InitializeFromVector(Source);
}

template<class T> Vector<T>& Vector<T>::operator=(Vector const & Source)
{
	if(this != &Source)
	{
		Free();
		InitializeFromVector(Source);
	}

	return *this;
}

template<class T> Vector<T>::~Vector()
{
	Free();
}

template<class T> void Vector<T>::Reserve(UInt Capacity)
{
	if(Capacity > this->Capacity)
		Allocate(Capacity);
}

template<class T> void Vector<T>::Shrink()
{
	if(Capacity > Length)
		Allocate(Length);
}

template<class T> void Vector<T>::Clear()
{
	Destroy(Begin(), End());
	Length = 0U;
}

template<class T> void Vector<T>::Free()
{
	if(VecPtr)
	{
		Destroy(Begin(), End());
		System::Memory::Free(VecPtr);
		VecPtr = NULL;
		Capacity = 0U;
		Length = 0U;
	}
}

template<class T> void Vector<T>::Add(T const & Value)
{
	Insert(Length, Value);
}

template<class T> void Vector<T>::Insert(UInt Position, T const & Value)
{
	T* Element;
	Bool LastElement;

	AutoAllocate();

	LastElement = Position >= Length;
	Element = VecPtr + (LastElement ? Length : Position);

	if(!LastElement)
	{
		ConstIterator Iterator = End();
		for(; Iterator > Element; --Iterator)
			Construct(Iterator, *(Iterator - 1));

		Destroy(Element);
	}

	Construct(Element, Value);
	++Length;
}

template<class T> void Vector<T>::Remove(UInt Position)
{
	ConstIterator Iterator, Last;

	if(Position >= Length)
		Position = Length - 1;

	Iterator = VecPtr + Position;
	Destroy(Iterator);
	Last = End() - 1;

	for(; Iterator < Last; ++Iterator)
		Construct(Iterator, *(Iterator + 1));

	--Length;
}

template<class T> T& Vector<T>::operator[](UInt Position)
{
	return *(VecPtr + Position);
}

template<class T> T const & Vector<T>::operator[](UInt Position) const
{
	return *(VecPtr + Position);
}

template<class T> UInt Vector<T>::GetCapacity() const
{
	return Capacity;
}

template<class T> UInt Vector<T>::GetLength() const
{
	return Length;
}

template<class T> typename Vector<T>::Iterator Vector<T>::Begin()
{
	return VecPtr;
}

template<class T> typename Vector<T>::Iterator Vector<T>::End()
{
	return VecPtr + Length;
}

template<class T> typename  Vector<T>::ConstIterator Vector<T>::Begin() const
{
	return VecPtr;
}

template<class T> typename  Vector<T>::ConstIterator Vector<T>::End() const
{
	return VecPtr + Length;
}

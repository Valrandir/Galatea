/* Vector.cpp */

/******************************************************************************/
/* Static *********************************************************************/
/******************************************************************************/

template<class T> typename Vector<T>::RawCopyEnum Vector<T>::DefaultMode = Vector<T>::RawCopyDisabled;

/******************************************************************************/
/* Private Functions **********************************************************/
/******************************************************************************/

template<class T> void Vector<T>::Deallocate()
{
	if(_origin)
	{
		if(_rawCopyMode == RawCopyDisabled)
			Destroy(_origin, _last);

		System::Memory::Free(_origin);

		_origin = NULL;
		_last = NULL;
		_end = NULL;
	}
}

template<class T> void Vector<T>::Allocate(UInt capacity)
{
	Element* newOrigin;

	newOrigin = (Element*)System::Memory::Alloc(sizeof(Element) * capacity);

	if(!IsEmpty())
	{
		if(_rawCopyMode == RawCopyEnabled)
			System::Memory::Copy(_origin, newOrigin, sizeof(Element) * GetLength());
		else
		{
			Move(newOrigin, _origin, _last);
			Destroy(_origin, _last);
		}
		System::Memory::Free(_origin);
	}

	_last = newOrigin + (_last - _origin);
	_end = newOrigin + capacity;
	_origin = newOrigin;
}

template <class T> void Vector<T>::AutoAllocate()
{
	if(_origin == NULL)
		Allocate(2U);
	else if(_last == _end)
		Allocate(GetCapacity() << 1U);
}

template <class T> void Vector<T>::Assign(ConstElement* target, Element *source) const
{
	new((VoidPtr)target) Element((Element&&)(*source));
}

template <class T> void Vector<T>::Construct(ConstElement* target, ConstElement *source) const
{
	new((VoidPtr)target) Element(*source);
}

template <class T> void Vector<T>::Destroy(ConstElement* target) const
{
	target->~Element();
}

template <class T> void Vector<T>::Destroy(ConstElement* begin, ConstElement* end) const
{
	while(begin != end)
		Destroy(begin++);
}

template <class T> void Vector<T>::Move(Element* target, Element* begin, Element* end) const
{
	if(_rawCopyMode == RawCopyEnabled)
		System::Memory::Move((VoidPtr)begin, (VoidPtr)target, sizeof(Element) * (end - begin));
	else
	{
		if(target < begin)
			while(begin != end)
				Assign(target++, begin++);
		else
		{
			target += end - begin - 1;
			while(begin != end)
				Assign(target--, --end);
		}
	}
}

template <class T> void Vector<T>::CopyToSelf(Vector const & source)
{
	ConstElement *it, *source_it, *source_end;

	Deallocate();
	_rawCopyMode = source._rawCopyMode;

	if(!source.IsEmpty())
	{
		Allocate(source.GetLength());

		it = _origin;
		source_it = source.Begin();
		source_end = source.End();
		while(source_it != source_end)
		{
			Construct(it++, source_it++);
			++_last;
		}
	}
}

template <class T> void Vector<T>::MoveToSelf(Vector & source)
{
	_rawCopyMode = source._rawCopyMode;

	if(source.IsEmpty())
		Deallocate();
	else
	{
		_origin = source._origin;
		_last = source._last;
		_end = source._end;
		source._origin = NULL;
		source._last = NULL;
		source._end = NULL;
	}
}

/******************************************************************************/
/* Constructors && Destructor *************************************************/
/******************************************************************************/

template<class T> Vector<T>::Vector() :
	_rawCopyMode(DefaultMode),
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{}

template<class T> Vector<T>::Vector(RawCopyEnum elementType = RawCopyDisabled) :
	_rawCopyMode(elementType),
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{}

template<class T> Vector<T>::Vector(UInt capacity, RawCopyEnum elementType = RawCopyDisabled) :
	_rawCopyMode(elementType),
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{
	Allocate(capacity);
}

template<class T> Vector<T>::Vector(Vector const & source) :
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{
	CopyToSelf(source);
}

template<class T> Vector<T>::Vector(Vector&& source) :
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{
	MoveToSelf(source);
}

template<class T> Vector<T>::~Vector()
{
	Deallocate();
}

/******************************************************************************/
/* Operators ******************************************************************/
/******************************************************************************/

template<class T> Vector<T>& Vector<T>::operator=(Vector const & source)
{
	if(this != &source)
		CopyToSelf(source);

	return *this;
}

template<class T> Vector<T>& Vector<T>::operator=(Vector&& source)
{
	if(this != &source)
		MoveToSelf(source);

	return *this;
}

template<class T> Vector<T>& Vector<T>::operator+=(Vector const & source)
{
	if(!source.IsEmpty())
		AddRange(source.Begin(), source.End());

	return *this;
}

template<class T> typename Vector<T>::Element& Vector<T>::operator[](UInt offset)
{
	return *(_origin + offset);
}

template<class T> typename Vector<T>::ConstElement& Vector<T>::operator[](UInt offset) const
{
	return *(_origin + offset);
}

/******************************************************************************/
/* Accesors *******************************************************************/
/******************************************************************************/

template<class T> typename Vector<T>::RawCopyEnum Vector<T>::GetElementType() const
{
	return _rawCopyMode;
}

template<class T> Bool Vector<T>::IsEmpty() const
{
	return _last == _origin;
}

template<class T> UInt Vector<T>::GetCapacity() const
{
	return _end - _origin;
}

template<class T> UInt Vector<T>::GetLength() const
{
	return _last - _origin;
}

/******************************************************************************/
/* Iterators ******************************************************************/
/******************************************************************************/

template<class T> typename Vector<T>::Element* Vector<T>::Begin()
{
	return _origin;
}

template<class T> typename Vector<T>::Element* Vector<T>::End()
{
	return _last;
}

template<class T> typename Vector<T>::Element* Vector<T>::RBegin()
{
	return _last - 1;
}

template<class T> typename Vector<T>::Element* Vector<T>::REnd()
{
	return _origin - 1;
}

template<class T> typename Vector<T>::ConstElement* Vector<T>::Begin() const
{
	return _origin;
}

template<class T> typename Vector<T>::ConstElement* Vector<T>::End() const
{
	return _last;
}

template<class T> typename Vector<T>::ConstElement* Vector<T>::RBegin() const
{
	return _last - 1;
}

template<class T> typename Vector<T>::ConstElement* Vector<T>::REnd() const
{
	return _origin - 1;
}

/******************************************************************************/
/* Public Functions ***********************************************************/
/******************************************************************************/

template<class T> void Vector<T>::Reserve(UInt capacity)
{
	if(capacity > GetCapacity())
		Allocate(capacity);
}

template<class T> void Vector<T>::Shrink()
{
	if(_end > _last)
		Allocate(GetLength());
}

template<class T> void Vector<T>::Clear()
{
	Destroy(_origin, _last);
	_last = _origin;
}

template<class T> void Vector<T>::Free()
{
	Deallocate();
}

template<class T> void Vector<T>::Add(ConstElement& value)
{
	AutoAllocate();
	Construct(_last, &value);
	++_last;
}

template<class T> void Vector<T>::AddRange(ConstElement* begin, ConstElement* end)
{
	if(begin && end && begin <= end)
	{
		Reserve(GetLength() + end - begin);
		while(begin != end)
			Construct(_last++, begin++);
	}
}

template<class T> void Vector<T>::Insert(Element& at, ConstElement& value)
{
	Int offset;
	Element* element;

	offset = &at - _origin;
	AutoAllocate();

	element = &operator[](offset);

	Move(element + 1, element, _last);
	++_last;

	Construct(element, &value);
}

template<class T> void Vector<T>::Insert(UInt offset, ConstElement& value)
{
	UInt length = GetLength();
	Element* element;

	//If the offset is past the end, insert at end
	if(offset > length)
		offset = length;

	AutoAllocate();

	element = &operator[](offset);

	Move(element + 1, element, _last);
	++_last;

	Construct(element, &value);
}

template<class T> void Vector<T>::Remove(Element& element)
{
	if(!IsEmpty() && &element)
	{
		Destroy(&element);

		if(&element != _last - 1)
		{
			Move(&element, &element + 1, _last);
			Destroy(_last - 1);
		}

		--_last;
	}
}

template<class T> void Vector<T>::Remove(UInt offset)
{
	UInt length;
	Element* element;

	if(!IsEmpty())
	{
		length = GetLength();

		//If the offset is past the end, delete last
		if(offset >= length)
			offset = length - 1;

		element = &operator[](offset);

		Destroy(element);

		if(element != _last - 1)
		{
			Move(element, element + 1, _last);
			Destroy(_last - 1);
		}

		--_last;
	}
}

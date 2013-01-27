/* Vector.cpp */

/******************************************************************************/
/* Private Functions **********************************************************/
/******************************************************************************/
template<class Element> void Vector<Element>::Deallocate()
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

template<class Element> void Vector<Element>::Allocate(UInt capacity)
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

template <class Element> void Vector<Element>::AutoAllocate()
{
	if(_origin == NULL)
		Allocate(2U);
	else if(_last == _end)
		Allocate(GetCapacity() << 1U);
}

template <class Element> void Vector<Element>::Assign(ConstElement* target, Element *source) const
{
	new((VoidPtr)target) Element((Element&&)(*source));
}

template <class Element> void Vector<Element>::Construct(ConstElement* target, ConstElement *source) const
{
	new((VoidPtr)target) Element(*source);
}

template <class Element> void Vector<Element>::Destroy(ConstElement* target) const
{
	target->~Element();
}

template <class Element> void Vector<Element>::Destroy(ConstElement* begin, ConstElement* end) const
{
	while(begin != end)
		Destroy(begin++);
}

template <class Element> void Vector<Element>::Move(Element* target, Element* begin, Element* end) const
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

template <class Element> void Vector<Element>::CopyToSelf(Vector const & source)
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

template <class Element> void Vector<Element>::MoveToSelf(Vector & source)
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

template<class Element> Vector<Element>::Vector(RawCopyEnum elementType = RawCopyDisabled) :
	_rawCopyMode(elementType),
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{}

template<class Element> Vector<Element>::Vector(UInt capacity, RawCopyEnum elementType = RawCopyDisabled) :
	_rawCopyMode(elementType),
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{
	Allocate(capacity);
}

template<class Element> Vector<Element>::Vector(Vector const & source) :
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{
	CopyToSelf(source);
}

template<class Element> Vector<Element>::Vector(Vector&& source) :
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{
	MoveToSelf(source);
}

template<class Element> Vector<Element>::~Vector()
{
	Deallocate();
}

/******************************************************************************/
/* Operators ******************************************************************/
/******************************************************************************/

template<class Element> Vector<Element>& Vector<Element>::operator=(Vector const & source)
{
	if(this != &source)
		CopyToSelf(source);

	return *this;
}

template<class Element> Vector<Element>& Vector<Element>::operator=(Vector&& source)
{
	if(this != &source)
		MoveToSelf(source);

	return *this;
}

template<class Element> Vector<Element>& Vector<Element>::operator+=(Vector const & source)
{
	int i, n;

	if(!source.IsEmpty())
	{
		n = source.GetLength();
		Reserve(GetLength() + n);

		for(i = 0; i < n; ++i)
			Add(source[i]);
	}

	return *this;
}

template<class Element> Element& Vector<Element>::operator[](UInt offset)
{
	return *(_origin + offset);
}

template<class Element> typename Vector<Element>::ConstElement& Vector<Element>::operator[](UInt offset) const
{
	return *(_origin + offset);
}

/******************************************************************************/
/* Accesors *******************************************************************/
/******************************************************************************/

template<class Element> typename Vector<Element>::RawCopyEnum Vector<Element>::GetElementType() const
{
	return _rawCopyMode;
}

template<class Element> Bool Vector<Element>::IsEmpty() const
{
	return _last == _origin;
}

template<class Element> UInt Vector<Element>::GetCapacity() const
{
	return _end - _origin;
}

template<class Element> UInt Vector<Element>::GetLength() const
{
	return _last - _origin;
}

/******************************************************************************/
/* Iterators ******************************************************************/
/******************************************************************************/

template<class Element> Element* Vector<Element>::Begin()
{
	return _origin;
}

template<class Element> Element* Vector<Element>::End()
{
	return _last;
}

template<class Element> Element* Vector<Element>::RBegin()
{
	return _last - 1;
}

template<class Element> Element* Vector<Element>::REnd()
{
	return _origin - 1;
}

template<class Element> typename Vector<Element>::ConstElement* Vector<Element>::Begin() const
{
	return _origin;
}

template<class Element> typename Vector<Element>::ConstElement* Vector<Element>::End() const
{
	return _last;
}

template<class Element> typename Vector<Element>::ConstElement* Vector<Element>::RBegin() const
{
	return _last - 1;
}

template<class Element> typename Vector<Element>::ConstElement* Vector<Element>::REnd() const
{
	return _origin - 1;
}

/******************************************************************************/
/* Public Functions ***********************************************************/
/******************************************************************************/

template<class Element> void Vector<Element>::Reserve(UInt capacity)
{
	if(capacity > GetCapacity())
		Allocate(capacity);
}

template<class Element> void Vector<Element>::Shrink()
{
	if(_end > _last)
		Allocate(GetLength());
}

template<class Element> void Vector<Element>::Clear()
{
	Destroy(_origin, _last);
	_last = _origin;
}

template<class Element> void Vector<Element>::Free()
{
	Deallocate();
}

template<class Element> void Vector<Element>::Add(ConstElement& value)
{
	AutoAllocate();
	Construct(_last, &value);
	++_last;
}

template<class Element> void Vector<Element>::Insert(Element& at, ConstElement& value)
{
	AutoAllocate();

	Move(&at + 1, &at, _last);
	++_last;

	Construct(&at, &value);
}

template<class Element> void Vector<Element>::Insert(UInt offset, ConstElement& value)
{
	UInt length = GetLength();
	Element* at;

	//If the offset is past the end, insert at end
	if(offset > length)
		offset = length;

	AutoAllocate();

	at = &operator[](offset);

	Move(at + 1, at, _last);
	++_last;

	Construct(at, &value);
}

template<class Element> void Vector<Element>::Remove(Element* element)
{
	if(!IsEmpty() && element)
	{
		Destroy(element);

		if(element != _last - 1)
		{
			Move(element, element + 1, _last);
			Destroy(_last - 1);
		}

		--_last;
	}
}

template<class Element> void Vector<Element>::Remove(UInt offset)
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

/* Vector.cpp */

/******************************************************************************/
/* Static *********************************************************************/
/******************************************************************************/

template<class T> typename Vector<T>::CtorModeEnum Vector<T>::DefaultMode = Vector<T>::CtorModeEnum::Always;

/******************************************************************************/
/* Private Functions **********************************************************/
/******************************************************************************/

template<class T> void Vector<T>::Deallocate()
{
	if(_origin)
	{
		if(_ctorMode != CtorModeEnum::Pod)
			Destroy(_origin, _last);

		Memory::Free(_origin);

		_origin = NULL;
		_last = NULL;
		_end = NULL;
	}
}

template<class T> void Vector<T>::Allocate(UInt capacity)
{
	Element* newOrigin;

	newOrigin = (Element*)Memory::Alloc(sizeof(Element) * capacity);

	if(!IsEmpty())
	{
		if(_ctorMode != CtorModeEnum::Always)
			Memory::Copy(_origin, newOrigin, sizeof(Element) * Length());
		else
		{
			MoveRange(newOrigin, _origin, _last);
			Destroy(_origin, _last);
		}
		Memory::Free(_origin);
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
		Allocate(Capacity() << 1U);
}

template <class T> void Vector<T>::Construct(ConstElement* target, ConstElement *source) const
{
	ASSERT(target);
	ASSERT(source);
	new((VoidPtr)target) Element(*source);
}

template <class T> void Vector<T>::Move(ConstElement* target, Element *source) const
{
	ASSERT(target);
	ASSERT(source);
	new((VoidPtr)target) Element((Element&&)(*source));
}

template <class T> void Vector<T>::Destroy(ConstElement* target) const
{
	ASSERT(target);
	target->~Element();
}

template <class T> void Vector<T>::Destroy(ConstElement* begin, ConstElement* end) const
{
	ASSERT(begin);
	ASSERT(end);

	while(begin != end)
		Destroy(begin++);
}

template <class T> void Vector<T>::MoveRange(Element* target, Element* begin, Element* end) const
{
	ASSERT(target);
	ASSERT(begin);
	ASSERT(end);

	if(_ctorMode != CtorModeEnum::Always)
		Memory::Move((VoidPtr)begin, (VoidPtr)target, sizeof(Element) * (end - begin));
	else
	{
		if(target < begin)
			while(begin != end)
				Move(target++, begin++);
		else
		{
			target += end - begin - 1;
			while(begin != end)
				Move(target--, --end);
		}
	}
}

template <class T> void Vector<T>::CopyToSelf(Vector const & source)
{
	UInt length;
	ConstElement *it, *source_it, *source_end;

	Deallocate();
	_ctorMode = source._ctorMode;

	if(!source.IsEmpty())
	{
		length = source.Length();
		Allocate(length);

		it = _origin;
		source_it = source.Begin();
		source_end = source.End();

		if(_ctorMode != CtorModeEnum::Always)
		{
			Memory::Move((VoidPtr)source_it, (VoidPtr)it, sizeof(Element) * length);
			_last += length;
		}
		else
			while(source_it != source_end)
			{
				Construct(it++, source_it++);
				++_last;
			}
	}
}

template <class T> void Vector<T>::MoveToSelf(Vector & source)
{
	Deallocate();
	_ctorMode = source._ctorMode;

	if(!source.IsEmpty())
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

template<class T> Vector<T>::Vector(CtorModeEnum ctorMode) :
	_ctorMode(ctorMode),
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{}

template<class T> Vector<T>::Vector(UInt capacity, CtorModeEnum ctorMode) :
	_ctorMode(ctorMode),
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

template<class T> Vector<T>::Vector(ConstElement* begin, ConstElement* end, CtorModeEnum ctorMode) :
	_ctorMode(ctorMode),
	_origin(NULL),
	_last(NULL),
	_end(NULL)
{
	AddRange(begin, end);
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
	ASSERT(_origin);
	ASSERT(offset >= 0U && offset < Length());
	return *(_origin + offset);
}

template<class T> typename Vector<T>::ConstElement& Vector<T>::operator[](UInt offset) const
{
	ASSERT(_origin);
	ASSERT(offset >= 0U && offset < Length());
	return *(_origin + offset);
}

/******************************************************************************/
/* Accesors *******************************************************************/
/******************************************************************************/

template<class T> typename Vector<T>::CtorModeEnum Vector<T>::CtorMode() const
{
	return _ctorMode;
}

template<class T> Bool Vector<T>::IsEmpty() const
{
	return _last == _origin;
}

template<class T> UInt Vector<T>::Capacity() const
{
	return _end - _origin;
}

template<class T> UInt Vector<T>::Length() const
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
	if(capacity > Capacity())
		Allocate(capacity);
}

template<class T> void Vector<T>::Shrink()
{
	if(_end > _last)
		Allocate(Length());
}

template<class T> void Vector<T>::Clear()
{
	if(!IsEmpty())
	{
		if(_ctorMode != CtorModeEnum::Pod)
			Destroy(_origin, _last);

		_last = _origin;
	}
}

template<class T> void Vector<T>::Free()
{
	Deallocate();
}

template<class T> void Vector<T>::Add(ConstElement& value)
{
	AutoAllocate();

	if(_ctorMode != CtorModeEnum::Pod)
		Construct(_last, &value);
	else
		*_last = value;

	++_last;
}

template<class T> void Vector<T>::AddRange(ConstElement* begin, ConstElement* end)
{
	UInt length;

	ASSERT(begin);
	ASSERT(end);
	ASSERT(begin != end);

	length = end - begin;
	Reserve(Length() + length);

	if(_ctorMode == CtorModeEnum::Pod)
	{
		Memory::Move((VoidPtr)begin, (VoidPtr)_last, sizeof(Element) * length);
		_last += length;
	}
	else
		while(begin != end)
			Construct(_last++, begin++);
}

template<class T> void Vector<T>::Insert(Element& at, ConstElement& value)
{
	Int offset;
	Element* element;

	offset = &at - _origin;
	AutoAllocate();
	element = _origin + offset;

	MoveRange(element + 1, element, _last);
	++_last;

	if(_ctorMode == CtorModeEnum::Pod)
		*element = value;
	else
		Construct(element, &value);
}

template<class T> void Vector<T>::Insert(UInt offset, ConstElement& value)
{
	UInt length = Length();
	Element* element;

	//If the offset is past the end, insert at end
	if(offset > length)
		offset = length;

	AutoAllocate();
	element = _origin + offset;

	MoveRange(element + 1, element, _last);
	++_last;

	if(_ctorMode == CtorModeEnum::Pod)
		*element = value;
	else
		Construct(element, &value);
}

template<class T> void Vector<T>::Remove(Element& element)
{
	if(!IsEmpty() && &element)
	{
		if(_ctorMode != CtorModeEnum::Pod)
			Destroy(&element);

		if(&element != _last - 1)
		{
			MoveRange(&element, &element + 1, _last);
			if(_ctorMode == CtorModeEnum::Always)
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
		length = Length();

		//If the offset is past the end, delete last
		if(offset >= length)
			offset = length - 1;

		element = _origin + offset;

		if(_ctorMode != CtorModeEnum::Pod)
			Destroy(element);

		if(element != _last - 1)
		{
			MoveRange(element, element + 1, _last);
			if(_ctorMode == CtorModeEnum::Always)
				Destroy(_last - 1);
		}

		--_last;
	}
}

template<class T> typename Vector<T>::Element* Vector<T>::DrivePointer(UInt future_length)
{
	_last = _origin + future_length;
	return _origin;
}

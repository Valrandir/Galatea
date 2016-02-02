#include "Buffer.hpp"

namespace Galatea
{
	void Buffer::Destroy()
	{
		if(_data)
		{
			Memory::Free(_data);
			_size = 0;
			_data = nullptr;
		}
	}

	Buffer& Buffer::Move(Buffer& source)
	{
		Destroy();
		_size = source._size;
		_data = source._data;
		source._size = 0;
		source._data = nullptr;
		return *this;
	}

	Buffer::Buffer() : _size{}, _data{} {}

	Buffer::Buffer(Int32 size)
	{
		_data = Memory::Alloc(ToUInt(size));
		_size = size;
	}

	Buffer::Buffer(Buffer&& source) : _data{}
	{
		Move(source);
	}

	Buffer& Buffer::operator=(Buffer&& source)
	{
		return Move(source);
	}

	Buffer::~Buffer()
	{
		Destroy();
	}

	void Buffer::Allocate(Int32 size)
	{
		Destroy();
		_data = Memory::Alloc(ToUInt(size));
		_size = size;
	}
}

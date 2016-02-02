#pragma once
#include "Galatea.hpp"

namespace Galatea
{
	class Buffer
	{
		Int32 _size;
		VoidPtr _data;

		void Destroy();
		Buffer& Move(Buffer& source);

		public:
		Buffer();
		Buffer(Int32 size);
		Buffer(const Buffer&) = delete;
		Buffer& operator=(const Buffer&) = delete;
		Buffer(Buffer&& source);
		Buffer& operator=(Buffer&& source);
		~Buffer();

		void Allocate(Int32 size);

		inline Int32 ByteSize() const { return _size; }
		inline const VoidPtr DataPtr() const { return _data; }
		inline VoidPtr DataPtr() { return _data; }
	};
}

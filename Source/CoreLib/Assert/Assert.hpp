#pragma once
#include "../Types.hpp"
#include "CoreException.hpp"

#ifdef CoreDebug
	#define ASSERT(func) if(!(func)) Core::Assert::Abort(CoreException(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__))
#else
	#define ASSERT
#endif

namespace Core
{
	class Assert
	{
		public:
		//Return true to continue with Abort, false to cancel Abort.
		typedef Bool (*AssertProc)(CoreException const &);

		private:
		static AssertProc _assertProc;

		Assert();
		Assert(Assert const &);
		Assert& operator=(Assert const &);

		public:
		static void SetAssertProc(AssertProc assertProc);
		static void Abort(CoreException const & ex);
	};
}

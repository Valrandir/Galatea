#pragma once
#include "../Types.hpp"
#include "CoreException.hpp"

#define ASSERT_COREX(func, corex) if(!(func) && corex) (*corex = CoreException(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__)).InitErr()

#ifdef CoreDebug
	#define ASSERT(func) if(!(func)) Core::Assert::Abort(CoreException(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__))
	#define ASSERT_RANGE(func) if(!(func)) Core::Assert::Abort(CoreException(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__, Assert::AssertTypeCStr(Assert::AssertTypeEnum::IndexOutOfRange)))
	#define ASSERT_PARAMETER(func) if(!(func)) Core::Assert::Abort(CoreException(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__, Assert::AssertTypeCStr(Assert::AssertTypeEnum::NullParameter)))
	#define ASSERT_SYSTEMCALL(func) if(!(func)) { CoreException ex(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__); ex.InitErr(); Core::Assert::Abort(ex); }
	#define ASSERT_MSG(func, msg) if(!(func)) Core::Assert::Abort(CoreException(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__, msg))
#else
	#define ASSERT
	#define ASSERT_RANGE
	#define ASSERT_PARAMETER
	#define ASSERT_SYSTEMCALL
	#define ASSERT_MSG
#endif

namespace Core
{
	class Assert
	{
		public:
		//Return true to continue with Abort, false to cancel Abort.
		typedef Bool (*AssertProc)(CoreException const &);

		enum AssertTypeEnum
		{
			Default = 0,
			IndexOutOfRange,
			NullParameter,
			SystemCall
		};

		private:
		static AssertProc _assertProc;

		Assert();
		Assert(Assert const &);
		Assert& operator=(Assert const &);

		static void SystemAbort(CoreException const & ex);

		public:
		static Bool Failing;
		static void SetAssertProc(AssertProc assertProc);
		static CStr AssertTypeCStr(AssertTypeEnum assertType);
		static void Abort(CoreException const & ex);
	};
}

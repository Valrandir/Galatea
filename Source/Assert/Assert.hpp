#pragma once
#include "../Types.hpp"
#include "Exception.hpp"

#define LOG_FILENAME Text("CoreLog.log")
#define ASSERT_COREX(func, corex) if(!(func) && corex) (*corex = Exception(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__)).InitFromLastErr()

#ifdef CoreDebug
	#define ASSERT(func) if(!(func)) Galatea::Assert::Abort(Exception(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__))
	#define ASSERT_RANGE(func) if(!(func)) Galatea::Assert::Abort(Exception(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__, Assert::AssertTypeToCStr(Assert::AssertTypeEnum::IndexOutOfRange)))
	#define ASSERT_PARAMETER(func) if(!(func)) Galatea::Assert::Abort(Exception(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__, Assert::AssertTypeToCStr(Assert::AssertTypeEnum::NullParameter)))
	#define ASSERT_SYSTEMCALL(func) if(!(func)) { Exception ex(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__); ex.InitFromLastErr(); Galatea::Assert::Abort(ex); }
	#define ASSERT_MSG(func, msg) if(!(func)) Galatea::Assert::Abort(Exception(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__, msg))
#else
	#define ASSERT
	#define ASSERT_RANGE
	#define ASSERT_PARAMETER
	#define ASSERT_SYSTEMCALL
	#define ASSERT_MSG
#endif

namespace Galatea
{
	class Assert
	{
		public:
		//Return true to continue with Abort, false to cancel Abort.
		typedef Bool (*AssertProc)(Exception const &);

		enum AssertTypeEnum
		{
			Default = 0,
			IndexOutOfRange,
			NullParameter,
			SystemCall
		};

		private:
		static AssertProc _assertProc;
		static CStr _logFileName;

		Assert();
		Assert(Assert const &);
		Assert& operator=(Assert const &);

		static void SystemAbort(Exception const & ex);

		public:
		static Bool Failing;
		static void SetAssertProc(AssertProc assertProc);
		static CStr GetLogFileName();
		static void SetLogFileName(CStr logFileName);
		static CStr AssertTypeToCStr(AssertTypeEnum assertType);
		static void Abort(Exception const & ex);
	};
}

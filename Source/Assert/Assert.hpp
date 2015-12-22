#pragma once
#include "../Types.hpp"
#include "Exception.hpp"

#define LOG_FILENAME Text("Galatea.log")
#define ASSERT_EXCEPTION(func, ex) if(!(func) && ex) (*ex = Exception(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__)).InitFromLastErr()

#ifdef GALATEA_BUILD_DEBUG
	#define ASSERT(func) if(!(func)) Galatea::Assert::Abort(Exception(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__))
	#define ASSERT_RANGE(func) if(!(func)) Galatea::Assert::Abort(Exception(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__, Assert::AssertTypeToCStr(Assert::AssertType::IndexOutOfRange)))
	#define ASSERT_PARAMETER(func) if(!(func)) Galatea::Assert::Abort(Exception(Text(#func), Text(__FUNCTION__), Text(__FILE__), __LINE__, Assert::AssertTypeToCStr(Assert::AssertType::NullParameter)))
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

		enum AssertType
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
		static CStr AssertTypeToCStr(AssertType assertType);
		static void Abort(Exception const & ex);
	};
}

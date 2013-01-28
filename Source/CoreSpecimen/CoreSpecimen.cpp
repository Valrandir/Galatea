extern void ErrTest();
extern void MemoryTest();
extern void ThreadTestByValue();
extern void ThreadTestByRef();
extern void ThreadedErrTest();
extern void TimeTest();
extern bool VectorTest();
extern bool StdVectorTest();
extern bool StringTest();

void CoreSpecimen()
{
	bool Skip = true;

	StringTest();

	//Force linking of all tests
	//Select which test to run in debug mode.
	if(!Skip)
	{
		ErrTest();
		MemoryTest();
		ThreadTestByValue();
		ThreadTestByRef();
		ThreadedErrTest();
		TimeTest();
		VectorTest();
		StringTest();
	}
}

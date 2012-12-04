extern void ErrTest();
extern void MemoryTest();
extern void ThreadTest();
extern void ThreadedErrTest();
extern void TimeTest();

void CoreSpecimen()
{
	bool Skip = true;

	//Force linking of all tests, select which test to run in debug mode.
	if(!Skip)
	{
		ErrTest();
		MemoryTest();
		ThreadTest();
		ThreadedErrTest();
		TimeTest();
	}
}

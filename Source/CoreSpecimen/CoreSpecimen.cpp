extern void ErrTest();
extern void MemoryTest();
extern void IThreadTest();
extern void TimeTest();

void CoreSpecimen()
{
	bool Skip = true;

	//Force linking of all tests, select which test to run in debug mode.
	if(!Skip)
	{
		ErrTest();
		MemoryTest();
		IThreadTest();
		TimeTest();
	}
}

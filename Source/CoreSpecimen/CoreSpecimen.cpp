extern void ErrTest();
extern void MemoryTest();
extern void TimeTest();

void CoreSpecimen()
{
	bool skip = true;
	if(!skip)
	{
		ErrTest();
		MemoryTest();
		TimeTest();
	}
}

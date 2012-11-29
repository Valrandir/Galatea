extern void MemoryTest();
extern void TimeTest();

void CoreSpecimen()
{
	bool skip = true;
	if(!skip)
	{
		MemoryTest();
		TimeTest();
	}
}

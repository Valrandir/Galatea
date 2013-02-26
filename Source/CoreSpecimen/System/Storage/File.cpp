#include "../../Core.hpp"

using namespace Core;
using namespace System::Storage;

Bool FileTest()
{
	Bool result = true;

	TChar const * fileName = Text("FileTest.txt");
	String message = Text("Hello World!") NewLine;
	UInt32 mode = File::OpenFlagEnum::OpenRead | File::OpenFlagEnum::OpenWrite | File::OpenOverwrite;
	File* file;
	UInt64 position;

	File::Delete(fileName);
	CHECK(File::Exists(fileName) == false);

	file = File::Open(fileName, mode);
	CHECK(file != 0);

	position = file->GetPosition();
	CHECK(position == 0U);

	file->Write((VoidPtr)message.GetTChar(), (UInt32)message.GetLength() * sizeof(TChar));
	position = file->GetPosition();
	CHECK(position == message.GetLength() * sizeof(TChar));

	file->Close();
	delete file;

	CHECK(File::Exists(fileName) == true);
	CHECK(File::Delete(fileName) == true);
	CHECK(File::Delete(fileName) == false);
	CHECK(File::Exists(fileName) == false);

	return result;
}

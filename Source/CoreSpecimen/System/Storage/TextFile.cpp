#include "../../Core.hpp"

using namespace Core;
using namespace System::Storage;

namespace TextFileTestNamespace
{
	CStr _fileName = Text("TextFileTest.txt");
	CStr _Content =
		Text("Polly Nomial and Curly Pi")
		NewLine
		NewLine
		Text("If you want to keep your expressions convergent, never allow them a single degree of freedom.")
		NewLine;

	Bool WriteTest()
	{
		Bool result = true;
		TextFile* textFile;
		UInt64 fileSize, textSize;

		textFile = TextFile::Create(_fileName);
		textFile->WriteText(_Content);
		DeletePtr(textFile);

		fileSize = File::GetFileSize(_fileName);
		textSize = String::GetTCharLength(_Content) * sizeof(TChar);
		CHECK(fileSize == textSize);

		return result;
	}

	Bool ReadAllTest()
	{
		Bool result = true;
		TextFile* textFile;
		String content;
		UInt64 textSize;

		textFile = TextFile::OpenReadOnly(_fileName);
		content = textFile->ReadAll();
		DeletePtr(textFile);

		textSize = String::GetTCharLength(_Content) * sizeof(TChar);
		CHECK(content.GetLength() == textSize);

		return result;
	}
}

Bool TextFileTest()
{
	Bool result = true;
	using namespace TextFileTestNamespace;

	CHECK(WriteTest());
	CHECK(ReadAllTest());

	File::Delete(_fileName);

	return result;
}

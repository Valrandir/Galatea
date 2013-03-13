#include "../Core.hpp"

using namespace Core;
using namespace Storage;

namespace TextFileTestNamespace
{
	CStr _fileName = Text("TextFileTest.txt");
	CStr _content =
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
		textFile->Write(_content);
		DeletePtr(textFile);

		fileSize = File::GetFileSize(_fileName);
		textSize = String::CStrLength(_content) * sizeof(TChar);
		CHECK fileSize == textSize;

		return result;
	}

	Bool WriteLineAppendTest()
	{
		Bool result = true;
		TextFile* textFile;
		UInt64 fileSize, textSize;

		textFile = TextFile::Append(_fileName);
		textFile->WriteLine(_content);
		DeletePtr(textFile);

		fileSize = File::GetFileSize(_fileName);
		textSize = String::CStrLength(_content) * sizeof(TChar);
		textSize *= 2;
		textSize += String::CStrLength(NewLine) * sizeof(TChar);
		CHECK fileSize == textSize;

		return result;
	}

	Bool ReadAllTest()
	{
		Bool result = true;

		String content = TextFile::ReadAll(_fileName);
		UInt64 fileSize = File::GetFileSize(_fileName);
		CHECK content.Length() == fileSize / sizeof(TChar);
		File::Delete(_fileName);

		return result;
	}

	Bool ReadLinesTest()
	{
		Bool result = true;
		TextFile* file;
		String::StrPtrVec* lines;

		//File is empty -> no lines
		file = TextFile::Create(_fileName);
		DeletePtr(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 0U;
		DeletePtr(lines);

		//File contains one space -> one line
		file = TextFile::Create(_fileName);
		file->Write(Text(" "));
		DeletePtr(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 1U;
		CHECK *(*lines)[0] == Text(" ");
		DeletePtr(lines);

		//File: contains NewLine only
		//Result: no line
		file = TextFile::Create(_fileName);
		file->Write(NewLine);
		DeletePtr(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 0U;
		DeletePtr(lines);

		//File: contains one line
		//Result: one line
		file = TextFile::Create(_fileName);
		file->Write(Text("Line 01"));
		DeletePtr(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 1U;
		CHECK *(*lines)[0] == Text("Line 01");
		DeletePtr(lines);

		//File: contains one line with NewLine at end
		//Result: one line
		file = TextFile::Append(_fileName);
		file->WriteLine();
		DeletePtr(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 1U;
		CHECK *(*lines)[0] == Text("Line 01");
		DeletePtr(lines);

		//File: contains two lines without a NewLine at end of second line
		//Result: two lines
		file = TextFile::Append(_fileName);
		file->Write(Text("Line 02"));
		DeletePtr(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 2U;
		CHECK *(*lines)[0] == Text("Line 01");
		CHECK *(*lines)[1] == Text("Line 02");
		DeletePtr(lines);

		//File: contains two lines with a NewLine at end of second line
		//Result: two lines
		file = TextFile::Append(_fileName);
		file->WriteLine();
		DeletePtr(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 2U;
		CHECK *(*lines)[0] == Text("Line 01");
		CHECK *(*lines)[1] == Text("Line 02");
		DeletePtr(lines);

		//File: contains seven lines with varied mix of NewLine \r \n
		//Result: seven lines
		file = TextFile::Append(_fileName);
		file->WriteLine(Text("Line 03\r"));
		file->WriteLine(Text("Line 04\n"));
		file->WriteLine(Text("Line 05\r\n"));
		file->WriteLine(Text("Line 06\n\r"));
		file->WriteLine(Text("Line 07"));
		DeletePtr(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 7U;
		CHECK *(*lines)[0] == Text("Line 01");
		CHECK *(*lines)[1] == Text("Line 02");
		CHECK *(*lines)[2] == Text("Line 03");
		CHECK *(*lines)[3] == Text("Line 04");
		CHECK *(*lines)[4] == Text("Line 05");
		CHECK *(*lines)[5] == Text("Line 06");
		CHECK *(*lines)[6] == Text("Line 07");
		DeletePtr(lines);

		File::Delete(_fileName);

		return result;
	}

	Bool WriteAllTest()
	{
		Bool result = true;
		String readBack;

		File::Delete(_fileName);

		TextFile::WriteAll(_fileName, _content);
		readBack = TextFile::ReadAll(_fileName);
		CHECK readBack == _content;

		File::Delete(_fileName);

		return result;
	}

	Bool AppendAllTest()
	{
		Bool result = true;
		String readBack;
		String expected(_content);

		File::Delete(_fileName);

		TextFile::WriteAll(_fileName, _content);
		TextFile::AppendAll(_fileName, _content);
		readBack = TextFile::ReadAll(_fileName);
		CHECK readBack == expected + _content;

		File::Delete(_fileName);

		return result;
	}
}

Bool TextFileTest()
{
	Bool result = true;
	using namespace TextFileTestNamespace;

	CHECK WriteTest();
	CHECK WriteLineAppendTest();
	CHECK ReadAllTest();
	CHECK ReadLinesTest();
	CHECK WriteAllTest();
	CHECK AppendAllTest();

	File::Delete(_fileName);

	return result;
}

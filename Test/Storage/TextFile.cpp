#include "../Galatea.hpp"

using namespace Galatea;
using namespace Storage;

namespace TextFileTestNamespace
{
	CStr _nullCStr = (CStr)0;
	CStr _fileName = Text("TextFileTest.txt");
	CStr _badFileName = Text("<MiG-25M>\\X-15//:Rocket.");

	CStr _content =
		Text("First line followed by two NewLine")
		NewLine
		NewLine
		Text("Fourth line followed by one NewLine")
		NewLine;

	void MakeFile()
	{
		auto file = TextFile::Create(_fileName);
		if(file) file->Write(_content);
		GALATEA_DELETE_PTR(file);
	}

	void DeleteFile()
	{
		File::Delete(_fileName);
	}

	Bool CreateTest()
	{
		Bool result = true;

		//Assert when fileName is null
		CHECK_ASSERT(TextFile::Create(_nullCStr));

		//Return null with bad filename
		CHECK TextFile::Create(_badFileName) == NULL;

		//Return ptr on success
		{
			TextFile *ptr = TextFile::Create(_fileName);
			CHECK ptr != NULL;
			GALATEA_DELETE_PTR(ptr);
		}

		DeleteFile();

		return result;
	}

	Bool AppendTest()
	{
		Bool result = true;

		//Assert when fileName is null
		CHECK_ASSERT(TextFile::Append(_nullCStr));

		//Return null with bad filename
		CHECK TextFile::Append(_badFileName) == NULL;

		MakeFile();

		//Return ptr on success
		//File position is at end
		{
			TextFile *ptr = TextFile::Append(_fileName);
			CHECK ptr != NULL;
			CHECK ptr->FileRef().GetSeekPos() == ptr->FileRef().GetFileSize();
			GALATEA_DELETE_PTR(ptr);
		}

		DeleteFile();

		return result;
	}

	Bool ReadLinesTest()
	{
		Bool result = true;
		TextFile* file;
		String::StrPtrVec* lines;
		Exception out_ex;

		//Assert when fileName is null
		CHECK_ASSERT(TextFile::ReadLines(_nullCStr));

		//Fail with bad filename
		lines = TextFile::ReadLines(_badFileName, &out_ex);
		CHECK lines != NULL;
		CHECK lines->Length() == 0U;
		CHECK String::Compare(String::Empty, out_ex.file) != 0;

		//File is empty -> no lines
		file = TextFile::Create(_fileName);
		GALATEA_DELETE_PTR(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 0U;
		GALATEA_DELETE_PTR(lines);

		//File contains one space -> one line
		file = TextFile::Create(_fileName);
		file->Write(Text(" "));
		GALATEA_DELETE_PTR(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 1U;
		CHECK *(*lines)[0] == Text(" ");
		GALATEA_DELETE_PTR(lines);

		//File: contains NewLine only
		//Result: no line
		file = TextFile::Create(_fileName);
		file->Write(NewLine);
		GALATEA_DELETE_PTR(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 0U;
		GALATEA_DELETE_PTR(lines);

		//File: contains one line
		//Result: one line
		file = TextFile::Create(_fileName);
		file->Write(Text("Line 01"));
		GALATEA_DELETE_PTR(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 1U;
		CHECK *(*lines)[0] == Text("Line 01");
		GALATEA_DELETE_PTR(lines);

		//File: contains one line with NewLine at end
		//Result: one line
		file = TextFile::Append(_fileName);
		file->WriteLine();
		GALATEA_DELETE_PTR(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 1U;
		CHECK *(*lines)[0] == Text("Line 01");
		GALATEA_DELETE_PTR(lines);

		//File: contains two lines without a NewLine at end of second line
		//Result: two lines
		file = TextFile::Append(_fileName);
		file->Write(Text("Line 02"));
		GALATEA_DELETE_PTR(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 2U;
		CHECK *(*lines)[0] == Text("Line 01");
		CHECK *(*lines)[1] == Text("Line 02");
		GALATEA_DELETE_PTR(lines);

		//File: contains two lines with a NewLine at end of second line
		//Result: two lines
		file = TextFile::Append(_fileName);
		file->WriteLine();
		GALATEA_DELETE_PTR(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 2U;
		CHECK *(*lines)[0] == Text("Line 01");
		CHECK *(*lines)[1] == Text("Line 02");
		GALATEA_DELETE_PTR(lines);

		//File: contains seven lines with varied mix of NewLine \r \n
		//Result: seven lines
		file = TextFile::Append(_fileName);
		file->WriteLine(Text("Line 03\r"));
		file->WriteLine(Text("Line 04\n"));
		file->WriteLine(Text("Line 05\r\n"));
		file->WriteLine(Text("Line 06\n\r"));
		file->WriteLine(Text("Line 07"));
		GALATEA_DELETE_PTR(file);
		lines = TextFile::ReadLines(_fileName);
		CHECK lines->Length() == 7U;
		CHECK *(*lines)[0] == Text("Line 01");
		CHECK *(*lines)[1] == Text("Line 02");
		CHECK *(*lines)[2] == Text("Line 03");
		CHECK *(*lines)[3] == Text("Line 04");
		CHECK *(*lines)[4] == Text("Line 05");
		CHECK *(*lines)[5] == Text("Line 06");
		CHECK *(*lines)[6] == Text("Line 07");
		GALATEA_DELETE_PTR(lines);

		DeleteFile();

		return result;
	}

	Bool ReadAllTest()
	{
		Bool result = true;
		String text;

		//Assert when fileName is null
		CHECK_ASSERT(TextFile::ReadAll(_nullCStr, text));

		//Fail with bad filename
		CHECK TextFile::ReadAll(_badFileName, text) == false;

		//Read file, read text size == file size
		MakeFile();
		CHECK TextFile::ReadAll(_fileName, text);
		UInt64 fileSize = File::GetFileSize(_fileName);

		CHECK text.Length() * sizeof(TChar) == fileSize;
		DeleteFile();

		return result;
	}

	Bool WriteTextTest()
	{
		Bool result = true;
		String readBack;

		DeleteFile();

		//Assert when fileName is null
		CHECK_ASSERT(TextFile::WriteText(_nullCStr, readBack));

		//Assert when text is null
		CHECK_ASSERT(TextFile::WriteText(_fileName, _nullCStr));

		//Fail with bad filename
		CHECK TextFile::WriteText(_badFileName, readBack) == false;

		//Write then read back the same text
		TextFile::WriteText(_fileName, _content);
		CHECK TextFile::ReadAll(_fileName, readBack);
		CHECK readBack == _content;

		DeleteFile();

		return result;
	}

	Bool AppendTextTest()
	{
		Bool result = true;
		String readBack;
		String expected(_content);

		DeleteFile();

		//Assert when fileName is null
		CHECK_ASSERT(TextFile::AppendText(_nullCStr, readBack));

		//Assert when text is null
		CHECK_ASSERT(TextFile::AppendText(_fileName, _nullCStr));

		//Fail with bad filename
		CHECK TextFile::AppendText(_badFileName, readBack) == false;

		//Write and Append then reacd back the same text
		TextFile::WriteText(_fileName, _content);
		TextFile::AppendText(_fileName, _content);
		CHECK TextFile::ReadAll(_fileName, readBack);
		CHECK readBack == expected + _content;

		DeleteFile();

		return result;
	}

	Bool WriteTest()
	{
		Bool result = true;
		TextFile* textFile;
		UInt64 fileSize, textSize;

		//Assert when file is not open
		textFile = TextFile::Create(_fileName);
		textFile->Close();
		CHECK_ASSERT(textFile->Write(_content));
		GALATEA_DELETE_PTR(textFile);

		//Assert when text is null
		textFile = TextFile::Create(_fileName);
		CHECK_ASSERT(textFile->Write(_nullCStr));
		GALATEA_DELETE_PTR(textFile);

		//Write, read back same length
		textFile = TextFile::Create(_fileName);
		textFile->Write(_content);
		GALATEA_DELETE_PTR(textFile);
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

		//Assert when file is not open
		textFile = TextFile::Create(_fileName);
		textFile->Close();
		CHECK_ASSERT(textFile->WriteLine(_content));
		GALATEA_DELETE_PTR(textFile);

		//Assert when text is null
		textFile = TextFile::Create(_fileName);
		CHECK_ASSERT(textFile->WriteLine(_nullCStr));
		GALATEA_DELETE_PTR(textFile);

		//Write, read back same length + length of NewLine
		MakeFile();
		textFile = TextFile::Append(_fileName);
		textFile->WriteLine(_content);
		GALATEA_DELETE_PTR(textFile);
		fileSize = File::GetFileSize(_fileName);
		textSize = String::CStrLength(_content) * sizeof(TChar);
		textSize *= 2;
		textSize += String::CStrLength(NewLine) * sizeof(TChar);
		CHECK fileSize == textSize;

		DeleteFile();

		return result;
	}
}

Bool TextFileTest()
{
	Bool result = true;
	using namespace TextFileTestNamespace;

	CHECK CreateTest();
	CHECK AppendTest();
	CHECK ReadAllTest();
	CHECK ReadLinesTest();
	CHECK WriteTextTest();
	CHECK AppendTextTest();
	CHECK WriteTest();
	CHECK WriteLineAppendTest();

	DeleteFile();

	return result;
}

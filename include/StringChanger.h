#pragma once
#include<string>
#include<Windows.h>
#include<locale>
using namespace std;
class StringChanger {
private:

public:
	// utf8(char) to utf16(wstring)
	static wstring Utf8ToWstring(const char *str);
	// wstring to string
	static string WstringToString(const wstring& str);
	//utf8(char) to utf16(string)
	static string Utf8ToGbk(const char *str);
	//string to wstring
	static wstring StringToWstring(const string& str);
};
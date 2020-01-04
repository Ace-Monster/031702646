#define _CRT_SECURE_NO_WARNINGS
#include"StringChanger.h"

wstring StringChanger::Utf8ToWstring(const char *s) {
	int l = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);
	wchar_t* gbk = new wchar_t[l + 1];
	memset(gbk, 0, l * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, s, -1, gbk, l);
	l = WideCharToMultiByte(CP_ACP, 0, gbk, -1, NULL, 0, NULL, NULL);
	char* tgbk = new char[l + 1];
	memset(tgbk, 0, l + 1);
	WideCharToMultiByte(CP_ACP, 0, gbk, -1, tgbk, l, NULL, NULL);
	string str(tgbk);
	if (gbk != 0) 
		delete[] gbk;
	if (tgbk != 0) 
		delete[] tgbk;
	size_t cnt = 0;
	setlocale(LC_ALL, "chs");
	const char* p = str.c_str();
	size_t ns = str.size() + 1;
	wchar_t *pd = new wchar_t[ns];
	wmemset(pd, 0, ns);
	mbstowcs_s(&cnt, pd, ns, p, ns);
	wstring ans = pd;
	delete[] pd;
	setlocale(LC_ALL, "C");
	return ans;
}

string StringChanger::WstringToString(const wstring& s) {
	unsigned l = s.size() * 4;
	setlocale(LC_CTYPE, "");
	char *p = new char[l];
	wcstombs(p, s.c_str(), l);
	string str(p);
	delete[] p;
	return str;
}

string StringChanger::Utf8ToGbk(const char *s) {
	return WstringToString(Utf8ToWstring(s));
}

wstring StringChanger::StringToWstring(const string& s) {
	
	unsigned len = s.size() * 2;
	setlocale(LC_CTYPE, ""); 
	wchar_t *p = new wchar_t[len];
	mbstowcs(p, s.c_str(), len);
	std::wstring str1(p);
	delete[] p;
	return str1;
	
}
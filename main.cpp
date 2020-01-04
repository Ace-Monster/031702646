#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"StringChanger.h"
#include<json\json.h>
#include<cstdio>
#include"Person.h"
#include"Trie.h"
#include<fstream>
#include <codecvt>
using namespace std;
const int maxn = 500;
char s[maxn];
Trie trie;
string GET_JSON_ADDRESS() {
	//return "a.json";
	TCHAR exeFullPath[MAX_PATH];
	memset(exeFullPath, 0, MAX_PATH);
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	// IF RELEASE
	return string(exeFullPath).substr(0, strlen(exeFullPath) - 27) + "resource\\address.json";
	// IF DEBUG
	//return string(exeFullPath).substr(0, strlen(exeFullPath) - 25) + "resource\\address.json";
}
/*
 * trieinit()进行字典树初始化，会消耗较大的时间(大约7s)，并非死循环
 */
int main(int argv, char* argc[]) {
	string infile = "resource\\in.txt", outfile = "resource\\out.json";
	cout << "正在初始化字典树" << endl;
	if (trie.init(GET_JSON_ADDRESS())) cout << "字典树生成成功" << endl;
	else cout << "生成失败" << endl;
	cout << "runing" << endl;
	fstream is;
	is.open(infile);
	Json::Value res;
	cout.imbue(locale("chs"));
	wcout.imbue(locale("chs"));
	int CNT = 0;
	while (is >> s) {
		CNT++;
		Person person;
		Json::Value tmp;
		char *p = s;
		while (*p < '1' || *p > '3') p++;
		int op = *p - '0';
		wstring wts = StringChanger().Utf8ToWstring(p+2);
		person.getName(wts);
		person.getPhone(wts);
		person.getCity(trie, StringChanger().WstringToString(wts));
		if (op == 3) person.fixAdress(trie, NULL, 3);
		tmp["姓名"] = person.name;
		tmp["手机"] = person.phone;
		for (int i = 0;i < 4;i++) {
			if (person.adress[i] == "直辖市") person.adress[i].clear();
			tmp["地址"].append(person.adress[i]);
		}
		if (op == 1) {
			tmp["地址"].append(person.adress[4]);
		}
		else {
			wts = StringChanger().StringToWstring(person.adress[4]);
			person.getAdress(wts);
			for (int i = 4;i < 7;i++)
				tmp["地址"].append(person.adress[i]);
		}
		res.append(tmp);
	}
	is.close();
	wofstream ous;
	ous.open(outfile);
	ous.imbue(locale(ous.getloc(), new codecvt_utf8<wchar_t, 0x10ffff, little_endian>));
	Json::FastWriter writer;
	ous << StringChanger().StringToWstring(writer.write(res)) << endl;
	cout << "ok" << CNT << endl;
	ous.close();
	return 0;
}
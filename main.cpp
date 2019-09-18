#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"StringChanger.h"
#include<json\json.h>
#include<cstdio>
#include"Person.h"
#include"Trie.h"
#include<fstream>
#include <codecvt>
#include<time.h>
using namespace std;
const int maxn = 500;
char s[maxn];
Trie trie;

/*
 * trieinit()�����ֵ�����ʼ���������Ľϴ��ʱ��(��Լ7s)��������ѭ��
 */
int main(int argv, char* argc[]) {
	string infile = "1.txt", outfile = "2.txt";
	//if (argv < 3) return 0;
	//infile = argc[1], outfile = argc[2];
	cout << "���ڳ�ʼ���ֵ���" << endl;
	if (trie.init()) cout << "�ֵ������ɳɹ�" << endl;
	else cout << "����ʧ��" << endl;
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
		for (int i = 0;i < 4;i++) {
			if (person.adress[i] == "ֱϽ��") person.adress[i].clear();
			tmp["��ַ"].append(person.adress[i]);
		}
		tmp["����"] = person.name;
		tmp["�绰"] = person.phone;
		if (op == 1) {
			tmp["��ַ"].append(person.adress[4]);
		}
		else {
			wts = StringChanger().StringToWstring(person.adress[4]);
			person.getAdress(wts);
			for (int i = 4;i < 7;i++)
				tmp["��ַ"].append(person.adress[i]);
		}
		res["answer"].append(tmp);
	}
	is.close();
	ofstream ous;
	ous.open(outfile);
	ous.imbue(locale(is.getloc(), new codecvt_utf8<wchar_t, 0x10ffff, little_endian>));
	Json::FastWriter writer;
	ous << writer.write(res) << endl;
	cout << "ok" << CNT << endl;
	ous.close();
	return 0;
}
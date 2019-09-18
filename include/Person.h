#pragma once
#include<string>
#include"Trie.h"
using namespace std;
struct Person {
	string name;
	string phone;
	string adress[7];
	Person() {
		name.clear();
		phone.clear();
		for (int i = 0;i < 7;i++) adress[i].clear();
	}
	//分离名字
	void getName(wstring &wts);
	//分离电话号码
	void getPhone(wstring &wts);
	//获取前四级地址
	void getCity(Trie &trie, string str);
	//获取后三级地址
	void getAdress(wstring &wts);
	//补全地址
	bool fixAdress(Trie &trie, trie_node *ptr, int rank);
	//检查直辖市
	bool checkCity();
private:
	bool isNum(wchar_t t);
	bool isCH(wchar_t t);
};
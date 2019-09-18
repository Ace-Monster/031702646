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
	//��������
	void getName(wstring &wts);
	//����绰����
	void getPhone(wstring &wts);
	//��ȡǰ�ļ���ַ
	void getCity(Trie &trie, string str);
	//��ȡ��������ַ
	void getAdress(wstring &wts);
	//��ȫ��ַ
	bool fixAdress(Trie &trie, trie_node *ptr, int rank);
	//���ֱϽ��
	bool checkCity();
private:
	bool isNum(wchar_t t);
	bool isCH(wchar_t t);
};
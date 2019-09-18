#pragma once
#include<string>
#include<Windows.h>
#include<locale>
#include<map>
#include<vector>
#include<set>
#include"json\json.h"
using namespace std;

struct trie_node {
	map<int, int> count;
	map<int, string> es;
	map<string, trie_node *> child;
	map<int, set<trie_node *> > father;
};

class Trie {
private:
	trie_node * root;
public:
	Trie();
	trie_node *insert(string str, int rank);
	trie_node *insert(trie_node *fa, string str, int rank);
	void seach(vector<string> &adr, string &str);
	trie_node* getPtr(string& s, int rank);
	bool init();
private:
	void init_getCounty(trie_node *fa, Json::Value& county);
	void init_getCity(trie_node *fa, Json::Value& city);
	void init_getProvice(Json::Value& provice);
};
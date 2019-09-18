#include"Trie.h"
#include<fstream>
#include"StringChanger.h"

Trie::Trie() {
	root = new trie_node();
}

trie_node *Trie::insert(string str, int rank) {
	int l = (int)str.size();
	if (root == NULL || !l) {
		return NULL;
	}
	trie_node *p = root;
	for (int i = 0;i < l;i += LC_CTYPE) {
		string s = str.substr(i, LC_CTYPE);
		auto it = p->child.find(s);
		if (it == p->child.end()) {
			trie_node *t = new trie_node();
			p->child.insert({ s, t });
			p = t;
		}
		else {
			p = it->second;
		}
		int tsz = (int)(p->es[rank].size());
		if (rank < 2 && (tsz == 0 || tsz > str.size())) {
			p->es[rank] = str;
			p->count[rank]++;
		}
	}
	int tsz = (int)(p->es[rank].size());
	if (rank >= 2 && (tsz == 0 || tsz > str.size())) {
		p->es[rank] = str;
		p->count[rank]++;
	}
	return p;
}

trie_node *Trie::insert(trie_node *fa, string str, int rank) {
	trie_node *p = insert(str, rank);
	p->father[rank].insert(fa);
	return p;
}

void Trie::seach(vector<string> &adr, string &str) {
	int n = (int)str.size();
	trie_node *p = root;
	int rank = 0;
	int ti = 0;
	for (int i = 0;i < n;) {
		if (rank == 4) {
			adr[4] = str.substr(ti, n - ti - 1);
			return;
		}
		string ts = str.substr(i, LC_CTYPE);
		auto it = p->child.find(ts);
		if (it == p->child.end()) {
			while (rank < 4) {
				int trank = rank++;
				if (p->count[trank]) {
					adr[trank] = p->es[trank];
					ti = i;
					p = root;
					break;
				}
			}
			if (rank == 4) {
				adr[4] = str.substr(ti, n - ti - 1);
				return;
			}
		}
		else {
			p = it->second;
			i += LC_CTYPE;
		}
	}
}

trie_node* Trie::getPtr(string& s, int rank) {
	int n = (int)s.size();
	trie_node *p = root;
	for (int i = 0;i < n;i += LC_CTYPE) {
		string ts = s.substr(i, LC_CTYPE);
		auto it = p->child.find(ts);
		p = it->second;
	}
	return p;
}

void Trie::init_getCounty(trie_node *fa, Json::Value& county) {
	trie_node *p = insert(fa, county["name"].asString(), 2);
	int sz = county["streets"].size();
	for (int i = 0;i < sz;i++) {
		insert(p, county["streets"][i].asString(), 3);
	}
}
void Trie::init_getCity(trie_node *fa, Json::Value& city) {
	trie_node *p = insert(fa, city["name"].asString(), 1);
	int  sz = city["districts"].size();
	for (int i = 0;i < sz;i++) {
		init_getCounty(p, city["districts"][i]);
	}
}
void Trie::init_getProvice(Json::Value& provice) {
	trie_node *p = insert(provice["name"].asString(), 0);
	int sz = provice["cities"].size();
	for (int i = 0;i < sz;i++) {
		init_getCity(p, provice["cities"][i]);
	}
}

const int maxn = 5000000;
char json_s[maxn];
bool Trie::init() {
	fstream is;
	is.open("a.json");
	is >> json_s;
	is.close();
	char *p = json_s;
	while (*p != '{') p++;
	string json = StringChanger().Utf8ToGbk(p);
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(json, root)) return false;
	int sz = root["provinces"].size();
	for (int i = 0;i < sz;i++) {
		init_getProvice(root["provinces"][i]);
	}
	return true;
}
#include"Trie.h"

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

void Trie::seach(Person& person, string str) {
	int n = (int)str.size();
	trie_node *p = root;
	int rank = 0;
	int ti = 0;
	for (int i = 0;i < n;) {
		if (rank == 4) {
			person.adress[4] = str.substr(ti, n - ti - 1);
			return;
		}
		string ts = str.substr(i, LC_CTYPE);
		auto it = p->child.find(ts);
		if (it == p->child.end()) {
			while (rank < 4) {
				int trank = rank++;
				if (p->count[trank]) {
					person.adress[trank] = p->es[trank];
					ti = i;
					p = root;
					break;
				}
			}
			if (rank == 4) {
				person.adress[4] = str.substr(ti, n - ti - 1);
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


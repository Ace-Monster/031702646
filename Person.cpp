#include"Person.h"
#include"StringChanger.h"
#include"Trie.h"
wstring load = StringChanger().StringToWstring("区道路街巷里弄胡同");
string spr[4] = { "北京","上海","天津","重庆" };
void Person::getName(wstring &wts) {
	int l = (int)wts.size();
	for (int i = 0;i < l;i++) {
		if (wts[i] == ',') {
			this->name = StringChanger().WstringToString(wts.substr(0, i));
			wts.erase(0, i + 1);
			return;
		}
	}
}

void Person::getPhone(wstring &wts) {
	int l = (int)wts.size();
	int cnt = 0;
	for (int i = 0;i < l;i++) {
		if (wts[i] >= '0' && wts[i] <= '9') cnt++;
		else cnt = 0;
		if (cnt == 11) {
			wstring tphone;
			tphone.assign(wts, i - cnt + 1, cnt);
			wts = wts.erase(i - cnt + 1, cnt);
			this->phone = StringChanger().WstringToString(tphone);
			break;
		}
	}
}

void Person::getCity(Trie &trie, string str) {
	vector<string> adr;
	adr.resize(10);
	string linecity[2] = { str.substr(0, 4), str.substr(0, 6) };
	for (int i = 0;i < 4;i++) {
		string tspr = spr[i] + "市";
		if (linecity[1] == tspr) {
			adress[0] = spr[i];
			adress[1] = tspr;
			str = str.erase(0, 6);
			break;
		}
		if (linecity[0] == spr[i]) {
			adress[0] = spr[i];
			adress[1] = tspr;
			str = str.erase(0, 4);
			break;
		}
	}
	trie.seach(adr, str);
	for (int i = 0;i < 5;i++) {
		if (adress[i].empty())
			adress[i] = adr[i];
	}
	//checkCity();
}

bool Person::isNum(wchar_t t) {
	return (t >= '0' && t <= '9');
}
bool Person::isCH(wchar_t t) {
	return t > 255;
}
void Person::getAdress(wstring &wts) {
	bool flag = 0;
	int l = (int)wts.size();
	for (int i = l - 1;i > 0;i--) {
		if (wts[i] == 21495 && !isCH(wts[i - 1])) {
			if (i < l - 1 && wts[i + 1] == 27004) continue;
			for (int j = i;j > 0;j--) {
				if (!isCH(wts[j]) && isCH(wts[j - 1])) {
					this->adress[4] = StringChanger().WstringToString(wts.substr(0, j));
					this->adress[5] = StringChanger().WstringToString(wts.substr(j, i - j + 1));
					if (i + 1 < l)
						this->adress[6] = StringChanger().WstringToString(wts.substr(i + 1, l - i - 1));
					return;
				}
			}
		}
	}
	for (int i = l - 1;i > 0;i--) {
		for (int j = 0;j < 6;j++) {
			if (wts[i] == load[j]) {
				this->adress[4] = StringChanger().WstringToString(wts.substr(0, i + 1));
				if (i + 1 < l)
					this->adress[6] = StringChanger().WstringToString(wts.substr(i + 1, l - i - 1));
				return;
			}
		}
		if (wts[i] == load[8] && wts[i - 1] == load[7]) {
			this->adress[4] = StringChanger().WstringToString(wts.substr(0, i + 1));
			if (i + 1 < l)
				this->adress[6] = StringChanger().WstringToString(wts.substr(i + 1, l - i - 1));
			return;
		}
	}
	this->adress[4].clear();
	this->adress[6] = StringChanger().WstringToString(wts);
}

bool Person::fixAdress(Trie &trie, trie_node *ptr, int rank) {
	if (ptr == NULL) {
		if (rank == 3 && !this->adress[3].size()) return false;
		ptr = trie.getPtr(this->adress[rank], rank);
	}
	if (this->adress[rank].size()) {
		if (ptr->es[rank] != this->adress[rank]) return false;
	}
	if (!rank) {
		this->adress[0] = ptr->es[rank];
		return true;
	}
	for (auto i : ptr->father[rank]) {
		if (fixAdress(trie, i, rank - 1)) {
			if (!this->adress[rank].size()) this->adress[rank] = ptr->es[rank];
			return true;
		}
	}
	return false;
}

bool Person::checkCity() {
	for (int i = 0;i < 4;i++) {
		string tspr = spr[i] + "市";
		if (this->adress[0] == spr[i] || this->adress[1] == tspr) {
			this->adress[0] = spr[i];
			this->adress[1] = tspr;
			return true;
		}
	}
	return false;
}
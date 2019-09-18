#pragma once
#include<string>
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
};
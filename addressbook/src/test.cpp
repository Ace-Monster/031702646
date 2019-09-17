//#pragma comment(lib, "Debug_json_vc71_libmt.lib")
//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<string>
//#include<vector>
//#include<json/json.h>
//#include<ostream>
//#include <fstream>
//#include<string>
//#include<Windows.h>
//#include<locale>
//#include"Trie.h"
//#include"StringChanger.h"
//using namespace std;
//wstring Utf8ToGbk(const char *src_str) {
//	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
//	wchar_t* wszGBK = new wchar_t[len + 1];
//	memset(wszGBK, 0, len * 2 + 2);
//	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
//	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
//	char* szGBK = new char[len + 1];
//	memset(szGBK, 0, len + 1);
//	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
//	string str(szGBK);
//	if (wszGBK) delete[] wszGBK;
//	if (szGBK) delete[] szGBK;
//	size_t cnt = 0;
//	setlocale(LC_ALL, "chs");
//	const char* pts = str.c_str();
//	size_t ns = str.size() + 1;
//	wchar_t *ptd = new wchar_t[ns];
//	wmemset(ptd, 0, ns);
//	mbstowcs_s(&cnt, ptd, ns, pts, ns);
//	wstring res = ptd;
//	delete[] ptd;
//	setlocale(LC_ALL, "C");
//	return res;
//}
//
//std::string WstringToString(const std::wstring str)
//{// wstring转string
//	unsigned len = str.size() * 4;
//	setlocale(LC_CTYPE, "");
//	char *p = new char[len];
//	wcstombs(p, str.c_str(), len);
//	std::string str1(p);
//	delete[] p;
//	return str1;
//}
//void ReadJsonFromString(const std::string strData)
//{
//	Json::Reader reader;
//	Json::Value root;
//	int nRole = 0;
//	if (!reader.parse(strData, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
//	{
//		return;
//	}
//	nRole = root["role_id"].asInt();
//	string ans = root["answer"]["姓名"].asString();
//	cout << ans << endl;
//}
//void ReadJsonFromFile() {
//	ifstream is("b.json", ios::binary);
//	if (!is.is_open())
//	{
//		cout << "open json file failed" << endl;
//		return;
//	}
//
//	Json::Reader reader;
//	Json::Value root;
//	int nRole = 0;
//	string strOccupation;
//	string strCamp;
//
//	if (reader.parse(is, root))
//	{
//		nRole = root["role_id"].asInt();
//		strOccupation = root["input"].asString();
//		strCamp = root["camp"].asString();
//	}
//	is.close();
//
//	cout << "role_id is: " << nRole << endl;
//	cout << "occupation is: " << strOccupation << endl;
//	cout << "camp is:" << strCamp << endl;
//
//	system("pause");
//	return;
//}
//void StringToJson() {
//	Json::Value val;
//	val["answer"]["name"] = "钟老师";
//	val["answer"]["地址"] = "33#319";
//	val["input"] = "zls33#319";
//	string ans = val.toStyledString();
//	
//	cout << ans << endl;
//}
//
//char s[5000000];
//Trie trie;
//void init_getCounty(Json::Value& county) {
//	trie.insert(county["name"].asString(), 2);
//	int sz = county["streets"].size();
//	for (int i = 0;i < sz;i++) {
//		trie.insert(county["streets"][i].asString(), 3);
//	}
//}
//void init_getCity(Json::Value& city) {
//	trie.insert(city["name"].asString(), 1);
//	int  sz = city["districts"].size();
//	for (int i = 0;i < sz;i++) {
//		init_getCounty(city["districts"][i]);
//	}
//}
//void init_getProvice(Json::Value& provice) {
//	trie.insert(provice["name"].asString(), 0);
//	int sz = provice["cities"].size();
//	for (int i = 0;i < sz;i++) {
//		init_getCity(provice["cities"][i]);
//	}
//}
//void init(string json) {
//	Json::Reader reader;
//	Json::Value root;
//	//reader.parse(json, root);
//	if (!reader.parse(json, root)) {
//		cout << "NO" << endl;
//		return;
//	}
//	int sz = root["provinces"].size();
//	//Json::Value tes = root["provinces"];
//	for (int i = 0;i < sz;i++) {
//		cout << root["provinces"][i]["name"].asString() << endl;
//		init_getProvice(root["provinces"][i]);
//	}
//	return;
//}
//int main() {
//	//StringToJson();
//	cout.imbue(locale("chs"));
//	wcout.imbue(locale("chs"));
//
//	
//	//if (i == 10) continue;
//	string url = "a.json";
//	fstream is;
//	is.open(url);
//	cout << url << endl;
//	is >> s;
//	is.close();
//	char *p = s;
//	while (*p != '{') p++;
//	init(StringChanger().Utf8ToGbk(p));
//	
//	
//	cout << "ok";
//	//wstring wts = Utf8ToGbk(s);
//	//wcout.imbue(locale("chs"));
//	//wcout << *wts.begin() << endl;
//	//string ts = WstringToString(wts);
//	//cout << ts << endl;
//	//ReadJsonFromString(ts);
//	//ReadJsonFromFile();
//	return 0;
//}
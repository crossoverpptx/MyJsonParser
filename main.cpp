#include "json/json.h"
#include "json/parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace crossoverpptx::json;
using namespace std;

int main() {
    string json_path = "E:/GitHub/MyJsonParser/test.json";
    ifstream fin(json_path);
    stringstream ss;
    ss << fin.rdbuf();
    const string &str = ss.str();

    Json v;
    v.parse(str);

    cout << v.str() << endl;

    string face = v["data"]["face"];
    int mid = v["data"]["mid"];
    string text = v["data"]["vip_label"]["text"];
    cout << "face : " << face << endl;
    cout << "mid : " << mid << endl;
    cout << "text : " << text << endl;
    return 0;
}

#include "json/json.h"
#include "json/parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace crossoverpptx::json;
using namespace std;

int main() {
    ifstream fin("E:/GitHub/TinyJsonParser/test.json");
    stringstream ss;
    ss << fin.rdbuf();
    const string &str = ss.str();

    Json v;
    v.parse(str);

    cout << v.str() << endl;

    bool isLogin = v["data"]["isLogin"];
    int current_level = v["data"]["level_info"]["current_level"];
    cout << "isLogin : " << isLogin << endl;
    cout << "current_level : " << current_level << endl;
    return 0;
}

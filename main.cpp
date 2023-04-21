#include "json/json.h"
#include "json/parser.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace myjson::json;

int main() {
    //const std::string & str = "\"hello\"";
    const std::string & str = "[1,2,3]";
    Json v;

    v.parse(str);
    std::cout << v.str() << std::endl;
    v.clear();

    // std::ifstream fin("test.json");
    // std::stringstream ss;
    // ss << fin.rdbuf();
    // const std::string & str = ss.str();

    // Json v;
    // v.parse(str);

    // std::cout << v.str() << std::endl;
    return 0;
}
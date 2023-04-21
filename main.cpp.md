#include <iostream>
#include "json/json.h"

using namespace myjson::json;

int main() {
    // /*      1. 基本类型      */
    // Json v1;
    // Json v2 = true;
    // Json v3 = 123;
    // Json v4 = 1.23;
    // Json v5 = "hello world";

    // /*
    //     下面的转换有点类似动态类型的语言
    //     需要实现基本类型的运算符重载
    // */
    // bool b = v2;
    // int i = v3;
    // double f = v4;
    // const std::string & s = v5;

    // /*      2. 数组类型      */
    // // 需要重载[]运算符
    // Json arr;
    // arr[0] = true;
    // arr[1] = 123;
    // arr.append(1.23);
    // arr.append("hello world");

    // std::cout << arr.str() << std::endl;

    // bool b = arr[0];
    // int i = arr[1];
    // double f = arr[2];
    // const std::string & s = arr[3];

    // /*      3. 对象类型      */
    // Json obj;
    // obj["bool"] = true;
    // obj["int"] = 123;
    // obj["double"] = 1.23;
    // obj["str"] = "hello world";

    // std::cout << obj.str() << std::endl;

    // /*      2. 数组类型      */
    // // 需要重载[]运算符
    // Json arr;
    // arr[0] = true;
    // arr[1] = 123;
    // arr[2] = 1.23;
    // arr[3] = "hello world";

    // for (auto it = arr.begin(); it != arr.end(); it++) {
    //     std::cout << (*it).str() << std::endl;
    // }

    // /*      5. 其他接口测试      */
    // Json arr;
    // arr[0] = true;
    // arr[1] = 123;
    // arr[2] = 1.23;
    // arr[3] = "hello world";

    // std::cout << arr.has(0) << std::endl;
    // std::cout << arr.has(4) << std::endl;

    // arr.remove(0);
    // std::cout << arr.str() << std::endl;

    // // /*      5. 其他接口测试      */
    // Json obj;
    // obj["bool"] = true;
    // obj["int"] = 123;
    // obj["double"] = 1.23;
    // obj["str"] = "hello world";

    // std::cout << obj.has("str") << std::endl;

    // obj.remove("str");
    // std::cout << obj.str() << std::endl;

    /*
        注意点：
        1. 每一个对象使用完后需要内存释放，比如：obj.clear();
        2. 浅拷贝不能重复内存释放
    */
    Json arr;
    arr[0] = true;
    arr[1] = 123;
    arr[2] = 1.23;

    Json obj;
    obj["bool"] = true;
    obj["int"] = 123;
    obj["double"] = 1.23;
    obj["arr"] = arr;

    std::cout << obj.str() << std::endl;

    //arr.clear();  // 无需对arr进行内存释放，否则会导致重复释放
                    // 实现深拷贝和移动构造，可以解决上面的问题
    obj.clear();

    return 0;
}
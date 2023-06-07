#ifndef JSON_H
#define JSON_H

#include <string>
#include <vector>
#include <map>

namespace crossoverpptx {  // 一级命名空间
namespace json {    // 二级命名空间

class Json {
public:
    enum Type { // json value的类型
        json_null = 0,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_array,
        json_object
    };

    // Json的构造函数
    // 1. 根据值进行构造
    Json(); // 默认构造函数
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char *value);           // C风格的字符串
    Json(const std::string &value);    // C++风格的字符串
    // 2. 根据类型进行构造
    Json(Type type);
    // 3. 根据其他Json进行构造
    Json(const Json & other);

    // 基本类型的运算符重载
    operator bool();
    operator int();
    operator double();
    operator std::string();

    // 数组[]运算符重载
    Json & operator [] (int index);
    void append(const Json &other);

    // 对象[]运算符重载
    Json & operator [] (const char *key);
    Json & operator [] (const std::string &key);

    // 赋值运算符重载
    void operator = (const Json &other);
    bool operator == (const Json &other);
    bool operator != (const Json &other);

    // 以字符串格式展示Json中的内容
    std::string str() const;
    
    void copy(const Json &other);

    // 对于数组、对象、其他Json格式的原有动态内存的释放
    void clear();

    // 定义一个迭代器，用于遍历数组
    typedef std::vector<Json>::iterator iterator;
    iterator begin() {
        return m_value.m_array->begin();
    }
    iterator end() {
        return m_value.m_array->end();
    }

    // 判断类型
    // const表示函数体内不能对类的对象进行修改
    bool isNull() const { return m_type == json_null; }
    bool isBool() const { return m_type == json_bool; }
    bool isInt() const { return m_type == json_int; }
    bool isDouble() const { return m_type == json_double; }
    bool isString() const { return m_type == json_string; }
    bool isArray() const { return m_type == json_array; }
    bool isObject() const { return m_type == json_object; }

    // 另外提供一个对基本运算符的显性的转换
    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    std::string asString() const;

    // 判断数组里有没有索引、对象里有没有key
    bool has(int index);
    bool has(const char *key);
    bool has(const std::string &key);

    // 删除
    void remove(int index);
    void remove(const char *key);
    void remove(const std::string &key);

    void parse(const std::string &str);
    
private:
    /*
        1. 用联合体表示Json的值，节省内存.
        2. union里放C++类必须给union写构造函数，即string等对象不能直接放在联合体内，因此这里我们放的是指针.
    */
    union  Value {  
        bool m_bool;
        int m_int;
        double m_double;
        std::string *m_string;
        std::vector<Json> *m_array;
        std::map<std::string, Json> *m_object;
    };

    Type m_type;    // Json的类型
    Value m_value;  // Json的值
    
};

}
}

#endif

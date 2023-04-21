#include "json.h"
#include "parser.h"
#include <stdexcept>
#include <sstream>

using namespace myjson::json;

Json::Json() : m_type(json_null) {  // 默认构造函数即传入空值，在初始化列表传入即可

}

Json::Json(bool value) : m_type(json_bool) {
    m_value.m_bool = value;
}

Json::Json(int value) : m_type(json_int) {
    m_value.m_int = value;
}

Json::Json(double value) : m_type(json_double) {
    m_value.m_double = value;
}

Json::Json(const char * value) : m_type(json_string) {
    m_value.m_string = new std::string(value);
}   

Json::Json(const std::string & value) : m_type(json_string) {
    m_value.m_string = new std::string(value);
}

Json::Json(Type type) : m_type(type) {
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = false; 
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_double:
            m_value.m_double = 0.0;
            break;
        case json_string:
            m_value.m_string = new std::string("");
            break;
        case json_array:
            m_value.m_array = new std::vector<Json>();
            break;
        case json_object:
            m_value.m_object = new std::map<std::string, Json>();
            break;
        default:
            break;
    }
}

Json::Json(const Json & other) {
    copy(other);
}

// 运算符重载
Json::operator bool() {
    if (m_type != json_bool) {
        throw std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}

Json::operator int() {
    if (m_type != json_int) {
        throw std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}

Json::operator double() {
    if (m_type != json_double) {
        throw std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}

Json::operator std::string() {
    if (m_type != json_string) {
        throw std::logic_error("type error, not string value");
    }
    return *(m_value.m_string); // 解引用，得到字符串的内容
}

// []运算符重载
Json & Json::operator [] (int index) {
    if (m_type != json_array) {
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    if (index < 0) {
        throw std::logic_error("array[] index < 0");
    }
    int size = (m_value.m_array)->size();
    if (index >= size) {
        for (int i = size; i <= index; i++) {
            (m_value.m_array)->push_back(Json());
        }
    }   
    return (m_value.m_array)->at(index);
}

void Json::append(const Json & other) {
    if (m_type != json_array) {
        clear();
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    (m_value.m_array)->push_back(other);
}

Json & Json::operator [] (const char * key) {
    std::string name(key);
    return (*(this))[name];
}

Json & Json::operator [] (const std::string & key) {
    if (m_type != json_object) {
        clear();
        m_type = json_object;
        m_value.m_object = new std::map<std::string, Json>();
    }
    return (*(m_value.m_object))[key];
}

void Json::operator = (const Json & other) {
    clear();
    copy(other);
}

bool Json::operator == (const Json & other) {
    if (m_type != other.m_type) {
        return false;
    }
    switch (m_type) {
        case json_null:
            return true;
        case json_bool:
            return m_value.m_bool == other.m_value.m_bool;
        case json_int:
            return m_value.m_int == other.m_value.m_int;
        case json_double:
            return m_value.m_double == other.m_value.m_double;
        case json_string:
            return *(m_value.m_string) == *(other.m_value.m_string);
        case json_array:
            return m_value.m_array == other.m_value.m_array; // 直接比较指针是否正确？
        case json_object: 
            return m_value.m_object == other.m_value.m_object; // 直接比较指针是否正确？
        default:
            break;
    }
    return false;
}

bool Json::operator != (const Json & other) {
    return !(*(this) == other);
}

std::string Json::str() const {
    std::stringstream ss;
    switch (m_type) {
        case json_null:
            ss << "null";
            break;
        case json_bool:
            if (m_value.m_bool) {
                ss << "true";
            } else {
                ss << "false";
            }
            break;
        case json_int:
            ss << m_value.m_int;
            break;
        case json_double:
            ss << m_value.m_double;
            break;
        case json_string:
            ss << "\"" << *(m_value.m_string) << "\"";
            break;
        case json_array: {
            ss << "[";
            for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++) {
                if (it != (m_value.m_array)->begin()) {
                    ss << ",";
                }
                ss << it->str();    // 递归调用
            }
            ss << "]";
            break;
        }            
        case json_object: {
            ss << "{";
            for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++) {
                if (it != (m_value.m_object)->begin()) {
                    ss << ",";
                }
                ss << "\"" << it->first << "\"" << ":" << it->second.str();    // 递归调用
            }
            ss << "}";
            break;
        }      
        default:
            break;
    }
    return ss.str();
}

void Json::copy(const Json & other) {
    m_type = other.m_type;
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = other.m_value.m_bool; 
            break;
        case json_int:
            m_value.m_int = other.m_value.m_int;
            break;
        case json_double:
            m_value.m_double = other.m_value.m_double;
            break;
        case json_string:
            // 为了防止动态内存频繁地创建和拷贝，这里就不对内存做深度的拷贝，使用的是浅拷贝，即直接将other类型，如字符串的指针拷贝过来即可
            // 可以极大地提升性能
            m_value.m_string = other.m_value.m_string;
            break;
        case json_array:
            m_value.m_array = new std::vector<Json>();
            break;
        case json_object:
            m_value.m_object = new std::map<std::string, Json>();
            break;
        default:
            break;
    }
}

void Json::clear() {
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = false; 
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_double:
            m_value.m_double = 0.0;
            break;
        case json_string:
            delete m_value.m_string;
            break;
        case json_array: {
            for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++) {
                it->clear();
            }
            delete m_value.m_array;
            break;
        }
        case json_object: {
            for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++) {
                (it->second).clear();
            }
            delete m_value.m_object;
            break;
        }
        default:
            break;
    }
    m_type = json_null;
}

// 另外提供一个对基本运算符的显性的转换
bool Json::asBool() const {
    if (m_type != json_bool) {
        throw std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}

int Json::asInt() const {
    if (m_type != json_int) {
        throw std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}

double Json::asDouble() const {
    if (m_type != json_double) {
        throw std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}

std::string Json::asString() const {
    if (m_type != json_string) {
        throw std::logic_error("type error, not string value");
    }
    return *(m_value.m_string); // 解引用，得到字符串的内容
}

// 判断数组里有没有索引、对象里有没有key
bool Json::has(int index) {
    if (m_type != json_array) {
        return false;
    }
    int size = (m_value.m_array)->size();
    return (index >= 0 && index < size);
}

bool Json::has(const char * key) {
    std::string name(key);
    return has(name);
}

bool Json::has(const std::string & key) {
    if (m_type != json_object) {
        return false;
    }
    return ((m_value.m_object)->find(key) != (m_value.m_object)->end());
}

// 删除
void Json::remove(int index) {
    if (m_type != json_array) {
        return;
    }
    int size = (m_value.m_array)->size();
    if (index < 0 || index >= size) {
        return;
    }
    (m_value.m_array)->at(index).clear();
    (m_value.m_array)->erase((m_value.m_array)->begin() + index);
}
void Json::remove(const char * key) {
    std::string name(key);
    remove(name);
}
void Json::remove(const std::string & key) {
    auto it = (m_value.m_object)->find(key);
    if (it == (m_value.m_object)->end()) {
        return;
    }
    (*(m_value.m_object))[key].clear();
    (m_value.m_object)->erase(key);
}

void Json::parse(const std::string & str) {
    Parser p;
    p.load(str);
    *this = p.parse();
}
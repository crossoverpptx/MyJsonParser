# TinyJsonParser
一个基于C++的简单Json解析器

## 涉及的知识点
- 面向对象设计
- 构造函数重载
- 函数重载
- 函数递归
- 运算符重载：bool、int、double、string
- 标准模板库：vector、map、ifstream、stringstream
- 内存管理：高效的内存使用，提升动态内存的使用率
- enum、union的巧用

## 详细设计
### 1. API设计（json.h和json.cpp）
- Json常用格式类型
- enum存储Json的类型
- union存储Json的值
- 构造函数：**在由其他Json构造时采用的是浅拷贝，不安全**
- 基本类型的运算符重载
```cpp
Json v1;
Json v2 = true;
Json v3 = 123;
Json v4 = 1.23;
Json v5 = "hello world";

bool b = v2;
int i = v3;
double f = v4;
const string &s = v5;
```
- 数组类型的运算符重载：实现[]和append添加函数，同时可以通过数组的形式将值转换成需要的基本类型
```cpp
Json arr;
arr[0] = true;
arr[1] = 123;
arr.append(1.23);
arr.append("hello world");

bool b = arr[0];
int i = arr[1];
double f = arr[2];
const string &s = arr[3] ;
```

**如果[]和append的旧的值是指针的话，会导致内存泄漏。**

- 以字符串格式展示Json中的内容

```cpp
Json arr;
arr[0] = true;
arr[1] = 123;
arr.append(1.23);
arr.append("hello world");

cout << arr.str() << endl;
```

- 对象[]运算符重载
- 赋值运算符重载
- copy函数模块化
- 对于数组、对象、其他Json格式的原有动态内存的释放，避免内存泄漏

- 定义一个迭代器，用于遍历数组

```cpp
Json arr;
arr[0] = true;
arr[1] = 123; 
arr[2] = 1.23;
arr[3] = "hello world";

for (auto it = arr.begin(); it != arr.end(); it++) {
	cout << (*it).str() << endl;
}
```

- ==和!=运算符重载：**直接比较指针肯定不正确**

- 判断类型

- 另外提供一个对基本运算符的显性的转换

- 判断数组、对象里有没有索引、对象里有没有key；remove元素

```cpp
Json arr;
arr[0] = true;
arr[1] = 123;
arr[2] = 1.23;
arr[3] = "hello world";

cout << arr.has(0) << endl;
cout << arr.has(4) << endl;
arr.remove(2);
cout << arr.str() << endl; 
/*=============================*/
Json obj;
obj["bool"] = true;
obj["int"] = 123;
obj["double"] = 1.23;
obj["str"] = "hello world";

cout << obj.has("123") << endl; 
obj.remove("str");
cout << obj.str() << endl; 
```

- 注意使用完后的内存释放

```cpp
Json obj;
obj["boo1"] = true;
obj["int"] = 123;
obj["double"] = 1.23;
obj["str"] = "hello world";

obj.clear();
```

### 2. Parser设计（parser.h和parser.cpp）

- Parser类构造函数、解析函数parse

```cpp
const string &str ="null";
Json v;
v.parse(str);
```

- 删除空格、获取下一个字符、各种字符解析函数

```cpp
const string &str = "true";
const string &str = "123";
const string &str = "1.23";
const string &str = "-1.23";
const string &str = "\"hello\"";
const string &str = "[1,2,3]";
const string &str = "[\"a\",1,2,3,true,false,null,1.23]";
const string &str = "{\"a\":1, \"b\":2, \"c\":3}";

Json v;
v.parse(str);
cout << v.str() << endl;
```

- 解析文件

```cpp
ifstream fin("./test.json");
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
```

## Bug处理

### 1. 解析数组有问题

```cpp
const string &str = "[1,2,3]";
Json v;
v.parse(str);
cout << v.str() << endl;

以下为输出：
ch1 : 1
ch2 : ,
breakpoint
terminate called after throwing an instance of 'std::logic_error*'
```

原因：parse开始先获取下一个字符，本应获取2，实际获取的是`,`，抛异常。

```cpp
Json Parser::parse() {
  char ch = get_next_token();
  switch (m_str[m_idx]) {
```

解决：在`Json Parser::parse_array()`函数中将182行的`m_idx++; `注释。

### 2. 读取文件数据失败	

```cpp
ifstream fin("./test.json");
stringstream ss;
ss << fin.rdbuf();
const string &str = ss.str();
cout << str << endl;

无输出
```

原因：不能使用相对路径，绝对路径没问题。`string json_path = "E:/GitHub/TinyJsonParser/test.json";`

### 3. 中文乱码

936代表GBK，65001代表utf-8。在终端输入 chcp 查看编码，使用 chcp 65001换成 utf-8 编码。

## 缺陷改进
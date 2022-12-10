#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <variant>
//исправить срр
namespace json {

class Node;
// Сохраните объявления Dict и Array без изменения
using Dict = std::map<std::string, Node>;
using Array = std::vector<Node>;

using Value = std::variant<std::nullptr_t, Array, Dict, bool, int, double, std::string>;

// Эта ошибка должна выбрасываться при ошибках парсинга JSON
class ParsingError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

class Node final : private Value {
public:
    /*Node() = default;
    Node (const Dict& val);
    Node (const Array& val);
    Node(std::nullptr_t val);
    Node(bool val);
    Node(int val);
    Node(double val);
    Node(const std::string& val);*/
    //наследуемся приватно: (реализован с помощью)

    using variant::variant;

    const Value& GetValue() const;

    //Следующие методы Node сообщают, хранится ли внутри значение некоторого типа
    bool IsInt() const;
    bool IsDouble() const; //Возвращает true, если в Node хранится int либо double.
    bool IsPureDouble() const; //Возвращает true, если в Node хранится double.
    bool IsBool() const;
    bool IsString() const;
    bool IsNull() const;
    bool IsArray() const;
    bool IsMap() const;
    //Ниже перечислены методы, которые возвращают хранящееся внутри Node значение заданного типа.
    //Если внутри содержится значение другого типа, должно выбрасываться исключение std::logic_error.
    int AsInt() const;
    bool AsBool() const;
    double AsDouble() const; //Возвращает значение типа double, если внутри хранится double либо int. В последнем случае возвращается приведённое в double значение.
    const std::string& AsString() const;
    const Array& AsArray() const;
    const Dict& AsMap() const;

    bool operator==(const Node &other) const;
    bool operator!=(const Node &other) const;

//private:
//    Value value_;
};

// ==============================================================

class Document {
public:
    Document() = default;
    explicit Document(Node root);

    const Node& GetRoot() const;

    bool operator==(const Document &other) const;
    bool operator!=(const Document &other) const;

private:
    Node root_{};
};

Document Load(std::istream& input);

Node LoadNode(std::istream& input);
Node LoadNumber(std::istream& input);
Node LoadString(std::istream& input);
Node LoadArray(std::istream& input);
Node LoadDict(std::istream& input);


void PrintValue(int i, std::ostream& out);
void PrintValue(double d, std::ostream& out);
void PrintValue(std::nullptr_t, std::ostream& out);
void PrintValue(const Array& array, std::ostream& out);
void PrintValue(const Dict& dict, std::ostream& out);
void PrintValue(const std::string& str, std::ostream& out);
void PrintValue(const bool bl, std::ostream& out);
void PrintNode(const Node& node, std::ostream& out);
void Print(const Document& doc, std::ostream& output);

}  // namespace json


/*
using namespace json;
using namespace std::literals;

namespace {

// Ниже даны тесты, проверяющие JSON-библиотеку.
// Можете воспользоваться ими, чтобы протестировать свой код.
// Раскомментируйте их по мере работы.


json::Document LoadJSON(const std::string& s) {
    std::istringstream strm(s);
    return json::Load(strm);
}

std::string Print(const Node& node) {
    std::ostringstream out;
    Print(Document{node}, out);
    return out.str();
}

void MustFailToLoad(const std::string& s) {
    try {
        LoadJSON(s);
        std::cerr << "ParsingError exception is expected on '"sv << s << "'"sv << std::endl;
        assert(false);
    } catch (const json::ParsingError&) {
        // ok
    } catch (const std::exception& e) {
        std::cerr << "exception thrown: "sv << e.what() << std::endl;
        assert(false);
    } catch (...) {
        std::cerr << "Unexpected error"sv << std::endl;
        assert(false);
    }
}

template <typename Fn>
void MustThrowLogicError(Fn fn) {
    try {
        fn();
        std::cerr << "logic_error is expected"sv << std::endl;
        assert(false);
    } catch (const std::logic_error&) {
        // ok
    } catch (const std::exception& e) {
        std::cerr << "exception thrown: "sv << e.what() << std::endl;
        assert(false);
    } catch (...) {
        std::cerr << "Unexpected error"sv << std::endl;
        assert(false);
    }
}

void TestNull() {
    Node null_node;
    assert(null_node.IsNull());
    assert(!null_node.IsInt());
    assert(!null_node.IsDouble());
    assert(!null_node.IsPureDouble());
    assert(!null_node.IsString());
    assert(!null_node.IsArray());
    assert(!null_node.IsMap());

    Node null_node1{nullptr};
    assert(null_node1.IsNull());

    assert(Print(null_node) == "null"s);
    assert(null_node == null_node1);
    assert(!(null_node != null_node1));

    const Node node = LoadJSON("null"s).GetRoot();
    assert(node.IsNull());
    assert(node == null_node);
    // Пробелы, табуляции и символы перевода строки между токенами JSON файла игнорируются
    assert(LoadJSON(" \t\r\n\n\r null \t\r\n\n\r "s).GetRoot() == null_node);
}

void TestNumbers() {
    const Node int_node{42};
    assert(int_node.IsInt());
    assert(int_node.AsInt() == 42);
    // целые числа являются подмножеством чисел с плавающей запятой
    assert(int_node.IsDouble());
    // Когда узел хранит int, можно получить соответствующее ему double-значение
    assert(int_node.AsDouble() == 42.0);
    assert(!int_node.IsPureDouble());
    assert(int_node == Node{42});
    // int и double - разные типы, поэтому не равны, даже когда хранят
    assert(int_node != Node{42.0});

    const Node dbl_node{123.45};
    assert(dbl_node.IsDouble());
    assert(dbl_node.AsDouble() == 123.45);
    assert(dbl_node.IsPureDouble());  // Значение содержит число с плавающей запятой
    assert(!dbl_node.IsInt());

    assert(Print(int_node) == "42"s);
    assert(Print(dbl_node) == "123.45"s);
    assert(Print(Node{-42}) == "-42"s);
    assert(Print(Node{-3.5}) == "-3.5"s);

    assert(LoadJSON("42"s).GetRoot() == int_node);
    assert(LoadJSON("123.45"s).GetRoot() == dbl_node);
    assert(LoadJSON("0.25"s).GetRoot().AsDouble() == 0.25);
    assert(LoadJSON("3e5"s).GetRoot().AsDouble() == 3e5);
    assert(LoadJSON("1.2e-5"s).GetRoot().AsDouble() == 1.2e-5);
    assert(LoadJSON("1.2e+5"s).GetRoot().AsDouble() == 1.2e5);
    assert(LoadJSON("-123456"s).GetRoot().AsInt() == -123456);
    assert(LoadJSON("0").GetRoot() == Node{0});
    assert(LoadJSON("0.0").GetRoot() == Node{0.0});
    // Пробелы, табуляции и символы перевода строки между токенами JSON файла игнорируются
    assert(LoadJSON(" \t\r\n\n\r 0.0 \t\r\n\n\r ").GetRoot() == Node{0.0});
}

void TestStrings() {
    Node str_node{"Hello, \"everybody\""s};
    assert(str_node.IsString());
    assert(str_node.AsString() == "Hello, \"everybody\""s);

    assert(!str_node.IsInt());
    assert(!str_node.IsDouble());

    assert(Print(str_node) == "\"Hello, \\\"everybody\\\"\""s);

    assert(LoadJSON(Print(str_node)).GetRoot() == str_node);
    const std::string escape_chars
        = R"("\r\n\t\"\\")"s;  // При чтении строкового литерала последовательности \r,\n,\t,\\,\"
    // преобразовываться в соответствующие символы.
    // При выводе эти символы должны экранироваться, кроме \t.
    assert(Print(LoadJSON(escape_chars).GetRoot()) == "\"\\r\\n\t\\\"\\\\\""s);
    // Пробелы, табуляции и символы перевода строки между токенами JSON файла игнорируются
    assert(LoadJSON("\t\r\n\n\r \"Hello\" \t\r\n\n\r ").GetRoot() == Node{"Hello"s});
}

void TestBool() {
    Node true_node{true};
    assert(true_node.IsBool());
    assert(true_node.AsBool());

    Node false_node{false};
    assert(false_node.IsBool());
    assert(!false_node.AsBool());

    assert(Print(true_node) == "true"s);
    assert(Print(false_node) == "false"s);

    assert(LoadJSON("true"s).GetRoot() == true_node);
    assert(LoadJSON("false"s).GetRoot() == false_node);
    assert(LoadJSON(" \t\r\n\n\r true \r\n"s).GetRoot() == true_node);
    assert(LoadJSON(" \t\r\n\n\r false \t\r\n\n\r "s).GetRoot() == false_node);
}

void TestArray() {
    //Array {1, 1.23, "Hello"s};
    Node arr_node{Array{1, 1.23, "Hello"s}};
    assert(arr_node.IsArray());
    const Array& arr = arr_node.AsArray();
    assert(arr.size() == 3);
    assert(arr.at(0).AsInt() == 1);

    assert(LoadJSON("[1,1.23,\"Hello\"]"s).GetRoot() == arr_node);
    assert(LoadJSON(Print(arr_node)).GetRoot() == arr_node);
    assert(LoadJSON(R"(  [ 1  ,  1.23,  "Hello"   ]   )"s).GetRoot() == arr_node);
    // Пробелы, табуляции и символы перевода строки между токенами JSON файла игнорируются
    assert(LoadJSON("[ 1 \r \n ,  \r\n\t 1.23, \n \n  \t\t  \"Hello\" \t \n  ] \n  "s).GetRoot()
           == arr_node);
}

void TestMap() {
    Node dict_node{Dict{{"key1"s, "value1"s}, {"key2"s, 42}}};
    assert(dict_node.IsMap());
    const Dict& dict = dict_node.AsMap();
    assert(dict.size() == 2);
    assert(dict.at("key1"s).AsString() == "value1"s);
    assert(dict.at("key2"s).AsInt() == 42);

    assert(LoadJSON("{ \"key1\": \"value1\", \"key2\": 42 }"s).GetRoot() == dict_node);
    assert(LoadJSON(Print(dict_node)).GetRoot() == dict_node);
    // Пробелы, табуляции и символы перевода строки между токенами JSON файла игнорируются
    assert(
        LoadJSON(
            "\t\r\n\n\r { \t\r\n\n\r \"key1\" \t\r\n\n\r: \t\r\n\n\r \"value1\" \t\r\n\n\r , \t\r\n\n\r \"key2\" \t\r\n\n\r : \t\r\n\n\r 42 \t\r\n\n\r } \t\r\n\n\r"s)
            .GetRoot()
        == dict_node);
}

void TestErrorHandling() {
    MustFailToLoad("["s);
    MustFailToLoad("]"s);

    MustFailToLoad("{"s);
    MustFailToLoad("}"s);

    MustFailToLoad("\"hello"s);  // незакрытая кавычка

    MustFailToLoad("tru"s);
    MustFailToLoad("fals"s);
    MustFailToLoad("nul"s);

    Node dbl_node{3.5};
    MustThrowLogicError([&dbl_node] {
        dbl_node.AsInt();
    });
    MustThrowLogicError([&dbl_node] {
        dbl_node.AsString();
    });
    MustThrowLogicError([&dbl_node] {
        dbl_node.AsArray();
    });

    Node array_node{Array{}};
    MustThrowLogicError([&array_node] {
        array_node.AsMap();
    });
    MustThrowLogicError([&array_node] {
        array_node.AsDouble();
    });
    MustThrowLogicError([&array_node] {
        array_node.AsBool();
    });
}

void Benchmark() {
    const auto start = std::chrono::steady_clock::now();
    Array arr;
    arr.reserve(1'000);
    for (int i = 0; i < 1'000; ++i) {
        arr.emplace_back(Dict{
            {"int"s, 42},
            {"double"s, 42.1},
            {"null"s, nullptr},
            {"string"s, "hello"s},
            {"array"s, Array{1, 2, 3}},
            {"bool"s, true},
            {"map"s, Dict{{"key"s, "value"s}}},
        });
    }
    std::stringstream strm;
    json::Print(Document{arr}, strm);
    const auto doc = json::Load(strm);
    assert(doc.GetRoot() == arr);
    const auto duration = std::chrono::steady_clock::now() - start;
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << "ms"sv
              << std::endl;
}
*/

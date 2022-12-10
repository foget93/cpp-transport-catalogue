#include "json.h"

using namespace std;

namespace json {

//namespace {

Node LoadArray(istream& input) {
    Array result;
    auto it = std::istreambuf_iterator<char>(input);
    auto end = std::istreambuf_iterator<char>();
    if (it == end) {
            throw ParsingError("B"s);
        }
    for (char c ; input >> c && c != ']';) {
        if (c != ',') {
            input.putback(c);
        }
        result.push_back(LoadNode(input));
    }
    return Node(move(result));
}

/*Node LoadInt(istream& input) {
    int result = 0;
    while (isdigit(input.peek())) {
        result *= 10;
        result += input.get() - '0';
    }
    return Node(result);
}*/

using Number = std::variant<int, double>;
Node LoadNumber(std::istream& input) {
    using namespace std::literals;

    std::string parsed_num;

    // Считывает в parsed_num очередной символ из input
    auto read_char = [&parsed_num, &input] {
        parsed_num += static_cast<char>(input.get());
        if (!input) {
            throw ParsingError("Failed to read number from stream"s);
        }
    };

    // Считывает одну или более цифр в parsed_num из input
    auto read_digits = [&input, read_char] {
        if (!std::isdigit(input.peek())) {
            throw ParsingError("A digit is expected"s);
        }
        while (std::isdigit(input.peek())) {
            read_char();
        }
    };
    if (input.peek() == 'n') {
        char t;
        input >> t;
        input >> t;
        if (t == 'u'&& input) {
            input >> t;
            if (t == 'l'&& input) {
               input >> t;
               if (t == 'l'&& input) {
                   return Node{nullptr};
               }
               else {throw ParsingError("A"s);}
            }
            else {throw ParsingError("A"s);}
        }
        else {throw ParsingError("A"s);}
    }
    if (input.peek() == 't') {
        char t;
        input >> t;
        input >> t;
        if (t == 'r'&& input) {
            input >> t;
            if (t == 'u'&& input) {
               input >> t;
               if (t == 'e'&& input) {
                   return Node{true};
               }
            }
        }

        //else {throw ParsingError("U"s);}
    }
    if (input.peek() == 'f') {
        char t;
        input >> t;
        input >> t;
        if (t == 'a'&& input) {
            input >> t;
            if (t == 'l'&& input) {
               input >> t;
               if (t == 's'&& input) {
                   input >> t;
                   if (t == 'e'&& input) {
                   return Node{false};
                   }
               }
            }
        }
    }
    if (input.peek() == '-') {
        read_char();
    }
    // Парсим целую часть числа
    if (input.peek() == '0') {
        read_char();
        // После 0 в JSON не могут идти другие цифры
    } else {
        read_digits();
    }

    bool is_int = true;
    // Парсим дробную часть числа
    if (input.peek() == '.') {
        read_char();
        read_digits();
        is_int = false;
    }

    // Парсим экспоненциальную часть числа
    if (int ch = input.peek(); ch == 'e' || ch == 'E') {
        read_char();
        if (ch = input.peek(); ch == '+' || ch == '-') {
            read_char();
        }
        read_digits();
        is_int = false;
    }
    try {
        if (is_int) {
            // Сначала пробуем преобразовать строку в int
            try {
                return Node(std::stoi(parsed_num));
            } catch (...) {
                // В случае неудачи, например, при переполнении,
                // код ниже попробует преобразовать строку в double
            }
        }
        return Node(std::stod(parsed_num));
    } catch (...) {
        throw ParsingError("Failed to convert "s + parsed_num + " to number"s);
    }
}

/*Node LoadString(istream& input) {
    string line;
    getline(input, line, '"');
    return Node(move(line));
}*/
Node LoadString(std::istream& input) {
    using namespace std::literals;

    auto it = std::istreambuf_iterator<char>(input);
    auto end = std::istreambuf_iterator<char>();
    std::string s;
    while (true) {
        if (it == end) {
            // Поток закончился до того, как встретили закрывающую кавычку?
            throw ParsingError("String parsing error");
        }
        const char ch = *it;
        if (ch == '"') {
            // Встретили закрывающую кавычку
            ++it;
            break;
        } else if (ch == '\\') {
            // Встретили начало escape-последовательности
            ++it;
            if (it == end) {
                // Поток завершился сразу после символа обратной косой черты
                throw ParsingError("String parsing error");
            }
            const char escaped_char = *(it);
            // Обрабатываем одну из последовательностей: \\, \n, \t, \r, \"
            switch (escaped_char) {
                case 'n':
                    s.push_back('\n');
                    break;
                case 't':
                    s.push_back('\t');
                    break;
                case 'r':
                    s.push_back('\r');
                    break;
                case '"':
                    s.push_back('"');
                    break;
                case '\\':
                    s.push_back('\\');
                    break;
                default:
                    // Встретили неизвестную escape-последовательность
                    throw ParsingError("Unrecognized escape sequence \\"s + escaped_char);
            }
        } else if (ch == '\n' || ch == '\r') {
            // Строковый литерал внутри- JSON не может прерываться символами \r или \n
            throw ParsingError("Unexpected end of line"s);
        } else {
            // Просто считываем очередной символ и помещаем его в результирующую строку
            s.push_back(ch);
        }
        ++it;
    }
    return Node(move(s));
}

Node LoadDict(std::istream& input) {
    Dict result;
    auto it = std::istreambuf_iterator<char>(input);
    auto end = std::istreambuf_iterator<char>();
    if (it == end) {
            throw ParsingError("Dict parsing error"s);
        }
    for (char c; input >> c && c != '}';) {
        if (c == ',') {
            input >> c;
        }
        Node a{LoadString(input)};
        string key = a.AsString();
        input >> c;
        result.insert({move(key), LoadNode(input)});
    }

    return Node(move(result));
}

Node LoadNode(std::istream& input) {
    char c;
    input >> c;

    if (c == '[') {
        return LoadArray(input);
    } else if (c == '{') {
        return LoadDict(input);
    } else if (c == '"') {
        return LoadString(input);
    } else {
        input.putback(c);
        return LoadNumber(input);
    }
}

//}  // namespace

/*Node::Node()
    : value_(nullptr) {}*/
/*
Node::Node(int val)
    : value_(move(val)) {}

Node::Node(double val)
    : value_(move(val)) {}

Node::Node(const string& val)
    : value_(move(val)) {}

Node::Node(nullptr_t val)
    : value_(move(val)) {}

Node::Node(bool val)
    : value_(move(val)) {}

Node::Node(const Dict& val)
    : value_(move(val)) {}

Node::Node(const Array& val)
    : value_(move(val)) {}
*/
const Value& Node::GetValue() const {
    return *this;
}

bool Node::IsInt() const {
    return holds_alternative<int>(*this);
}
//Возвращает true, если в Node хранится int либо double.

bool Node::IsDouble() const {
    return holds_alternative<double>(*this) || holds_alternative<int>(*this);
}

//Возвращает true, если в Node хранится double.
bool Node::IsPureDouble() const {
    return holds_alternative<double>(*this);
}

bool Node::IsBool() const {
    return holds_alternative<bool>(*this);
}

bool Node::IsString() const {
    return holds_alternative<string>(*this);
}

bool Node::IsNull() const {
    return holds_alternative<nullptr_t>(*this);
}

bool Node::IsArray() const {
    return holds_alternative<Array>(*this);
}

bool Node::IsMap() const {
    return holds_alternative<Dict>(*this);
}

int Node::AsInt() const {
    if (!IsInt()) {
        throw std::logic_error("Not an int"s);
    }
    return get<int>(*this);
}

bool Node::AsBool() const {
    if (!IsBool()) {
        throw std::logic_error("Not an bool"s);
    }
    return get<bool>(*this);
}

//Возвращает значение типа double, если внутри хранится double либо int. В последнем случае возвращается приведённое в double значение.
double Node::AsDouble() const {
    if (!IsDouble()) {
        throw std::logic_error("Not an double"s);
    }
    if (IsPureDouble()) {
        return get<double>(*this);
    }
    else {
        return static_cast<double>(get<int>(*this));
    }
}

const string& Node::AsString() const {
    if (!IsString()) {
        throw std::logic_error("Not an std::string"s);
    }
    return get<string>(*this);
}

const Array& Node::AsArray() const {
    if (!IsArray()) {
        throw std::logic_error("Not an std::vector<Node> (Array)"s);
    }
    return get<Array>(*this);
}
const Dict& Node::AsMap() const {
    if (!IsMap()) {
        throw std::logic_error("Not an std::map<std::string, Node> (Dict)");
    }
    return get<Dict>(*this);
}
//Document::Document() : root_(nullptr) {}
Document::Document(Node root)
    : root_(move(root)) {
}

const Node& Document::GetRoot() const {
    return root_;
}

Document Load(istream& input) {
    return Document{LoadNode(input)};
}

void Print(const Document& doc, std::ostream& output) {
    PrintNode(doc.GetRoot(), output);
}


void PrintValue(std::nullptr_t, std::ostream& out) {
    out << "null"sv;
}
void PrintValue(const Array& array, std::ostream& out) {
    out<<'[';
    int i = 0;
    if (i == 1) {
        out << ", "sv;
    }
    for (const auto& a : array) {
        if (i == 1) {
            out << ", "sv;
        }
        PrintNode(a, out);
        i = 1;
    }
    out<<']';
}
void PrintValue(const Dict& dict, std::ostream& out) {
    out<<'{';
    int i = 0;
    if (i == 1) {
        out << ", "sv;
    }
    for (const auto& [a, b] : dict) {
        if (i == 1) {
            out << ", "sv;
        }
        out << "\""sv;
        out << a << "\": "sv;
        //if (b.IsString()) {out << "\""sv;}
        PrintNode(b, out);
        //if (b.IsString()) {out << "\""sv;}
        i = 1;
    }
    out<<'}';
}
void PrintValue(const std::string& str, std::ostream& out) {
    out << "\""s;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i]=='"') {
            out << "\\\""s;
        }
        else if (str[i]=='\r') {
            out << "\\r"s;
        }
        else if (str[i]=='\n') {
            out << "\\n"s;
        }
        else if (str[i]=='\\') {
            out << "\\\\"s;
        }
        else { out << str[i];}
    }
    out << "\""s;
}
void PrintValue(const bool bl, std::ostream& out) {
    if (bl) {
        out << "true"s;
    }
    else { out << "false"s;}
}
void PrintValue(int i, std::ostream& out) {
    out << i;
}
void PrintValue(double d, std::ostream& out) {
    out << d;
}

void PrintNode(const Node& node, std::ostream& out) {
    std::visit(
        [&out](const auto& value){ PrintValue(value, out); },
        node.GetValue());
}


bool Node::operator==(const Node& other) const {
    return *this == other.GetValue();
}

bool Node::operator!=(const Node& other) const {
    return !(*this == other);
}

bool Document::operator==(const Document& other) const {
    return this->GetRoot() == other.GetRoot();
}

bool Document::operator!=(const Document& other) const {
    return !(*this == other);
}


}  // namespace json

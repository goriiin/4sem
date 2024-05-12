#include <iostream>
#include <string>
#include <vector>

void run(std::istream &in, std::ostream &out);

void remove_extra_spaces(std::string &str);

int main() {
    run(std::cin, std::cout);
    return 0;
}

// TODO: enum с ошибками возврат <int, int> или <int> с ошибкой

enum errors {
    NO_ERROR = 0,
    NAME_TYPE_ERROR,
    NUM_TYPE_ERROR,
    NUM_IDENTIFIER_ERROR,
    NAME_IDENTIFIER_ERROR,
    NO_SMILE,
    PARENTHESES,
    NO_SAD
};

enum types {
    NO_TYPE = -1,
    VOID = 0,
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    BOOL
};

enum key_words {
    SMILE, // )
    SAD, // (
    COMMA,
    SEMICOLON,
};

struct parametr {
    types type;
    int ptr_count;
    std::string ident;
    int square_count;
    std::vector<int> num; // -1 если нет, иначе UNSIGNED
};

struct func {
    types ret_type;
    std::string ident;
    std::vector<parametr> parameters;

    func(types _type, std::string &name, std::vector<parametr> &p) : ret_type(_type), ident(name), parameters(p) {}
};

errors check_parentheses(std::string &str, size_t &ptr);

// find_func_identifier - возвращает index ошибки
// string - возвращаем название
std::pair<errors, std::string> find_func_identifier(std::string &str, size_t &ptr);

std::pair<int, std::vector<parametr>> get_parameters(std::string &str, size_t &ptr);

std::pair<types, errors> get_ret_type(std::string &str, size_t &ptr);

void run(std::istream &in, std::ostream &out) {
    std::string input;
    std::getline(in, input);
    remove_extra_spaces(input);
    size_t ptr = 0;

    auto c = get_ret_type(input, ptr);
    if (c.second != errors::NO_ERROR) {
        out << "ERROR type" << c.second << std::endl;
        return;
    }

    auto b = find_func_identifier(input, ptr);
    if (b.first != errors::NO_ERROR) {
        out << "ERROR name" << b.first << std::endl;
        return;
    }
    out << b.second;
    auto a = check_parentheses(input, ptr);
    if (a != errors::NO_ERROR) {
        out << "ERROR parentheses" << a << std::endl;
        return;
    }
    auto p = get_parameters(input, ptr);
    if (!p.first) {
        out << "ERROR parameters";
        return;
    }
}

std::pair<types, errors> get_type(std::string &str) {
    if (str == "int") {
        return {types::INT, errors::NO_ERROR};
    } else if (str == "void") {
        return {types::VOID, errors::NO_ERROR};
    } else if (str == "double") {
        return {types::DOUBLE, errors::NO_ERROR};
    } else if (str == "float") {
        return {types::DOUBLE, errors::NO_ERROR};
    } else if (str == "char") {
        return {types::CHAR, errors::NO_ERROR};
    }
    return {types::NO_TYPE, errors::NAME_TYPE_ERROR};
}

std::pair<types, errors> get_ret_type(std::string &str, size_t &ptr) {
    std::string type_name;
    for (auto &ch: str) {
        if (ch == ' ' || ch == '*')
            break;

        ++ptr;
        type_name += ch;
    }

    if (type_name[0] >= '0' && type_name[0] <= '9')
        return {types::NO_TYPE, errors::NUM_TYPE_ERROR};

    return get_type(type_name);
}

std::pair<int, std::vector<parametr>> get_parameters(std::string &str, size_t &ptr) {
    return {};
}

std::pair<errors, std::string> find_func_identifier(std::string &str, size_t &ptr) {
    std::string name;
    size_t j = ptr;
    for (size_t i = j; i < str.size(); ++i) {
        auto ch = str[i];

        if (ch == ' ' || ch == '(')
            break;
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            name += ch;
        } else {
            return {errors::NAME_IDENTIFIER_ERROR, ""};
        }
        ++ptr;
    }
    if (name[0] <= '9' && name[0] >= '0')
        return {errors::NUM_IDENTIFIER_ERROR, ""};
    return {errors::NO_ERROR,name};
}



errors check_parentheses(std::string &str, size_t &ptr) {
    int smile_ptr = str.find('(');
    int sad_ptr = str.find(')');

    if (smile_ptr == -1){
        std::cout << "_1er\n";
        return errors::NO_SMILE;
    }
    if (sad_ptr == -1){
        std::cout << "_2er\n";
        return errors::NO_SAD;
    }

    std::cout << ptr << " " << smile_ptr << " " << sad_ptr;

    if (smile_ptr < ptr){
        std::cout << "_3er\n";
        return errors::NO_SMILE;
    }else if (smile_ptr > sad_ptr){
        std::cout << "_4er\n";
        return errors::PARENTHESES;
    }

    ptr = ++smile_ptr;
    return errors::NO_ERROR;
}

void remove_extra_spaces(std::string &str) {
    std::string out;

    bool ch_flag = false;
    bool flag = false;


    for (auto &ch: str) {
        if (ch == ' ' || ch == ';') {
            if (ch == ';') {
                out += ch;
                break;
            }
            if (flag || !ch_flag) {
                continue;
            } else {
                flag = true;
                out += ch;
            }
        } else {
            ch_flag = true;
            flag = false;
            out += ch;
        }
    }

    str = std::move(out);
}

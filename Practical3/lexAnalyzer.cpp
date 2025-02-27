#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

unordered_set<string> keywords = {"void", "int", "long", "float", "struct", "return", "scanf", "printf"};

bool isKeyword(const string &str) {
    return keywords.find(str) != keywords.end();
}

bool isNumber(const string &str) {
    for (char ch : str) {
        if (!isdigit(ch))
            return false;
    }
    
    return true;
}

bool isOperator(char ch) {
    string operators = "+-*/%=<>&|!";
    return operators.find(ch) != string::npos;
}

void analyzeLexemes(const string &code) {
    int len = code.length();
    string lexeme = "";

    for (int i = 0; i < len; i++) {
        char ch = code[i];

        if (isspace(ch)) {
            continue;
        }

        if (isalpha(ch) || ch == '_') {
            lexeme = "";
            while (isalnum(code[i]) || code[i] == '_') {
                lexeme += code[i++];
            }
            i--;
            if (isKeyword(lexeme)) {
                cout << lexeme << " : Keyword\n";
            } else {
                cout << lexeme << " : Identifier\n";
            }
        }
        else if (isdigit(ch)) {
            lexeme = "";
            while (isdigit(code[i])) {
                lexeme += code[i++];
            }
            i--;
            cout << lexeme << " : Number\n";
        }
        else if (isOperator(ch)) {
            cout << ch << " : Operator\n";
        }
        else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == ';' || ch == ',') {
            cout << ch << " : Special Symbol\n";
        }
    }
}

int main() {
    ifstream MyReadFile("testCase1.c"); 

    string code;
    string str;

    while (getline (MyReadFile, code)) {
        str += code;
    }

    cout << "Lexical Analysis Result:\n";
    analyzeLexemes(str);

    return 0;
}

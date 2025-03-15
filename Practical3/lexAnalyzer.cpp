#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

unordered_set<string> keywords = {"int", "char", "return", "if", "else", "while", "for", "break", "continue"};
unordered_set<char> operators = {'+', '-', '*', '/', '=', '>', '<', '!'};
unordered_set<char> punctuation = {';', ',', '(', ')', '{', '}'};
unordered_set<string> symbolTable;
vector<string> lexicalErrors;

bool isValidIdentifier(const string &s) {
    if (!isalpha(s[0]) && s[0] != '_') return false;
    for (char c : s) {
        if (!isalnum(c) && c != '_') return false;
    }
    return true;
}

bool isConstant(const string &s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void tokenize(const string &code) {
    string token;
    bool inString = false, inChar = false, inComment = false;
    vector<string> tokens;
    
    for (size_t i = 0; i < code.length(); i++) {
        char c = code[i];

        if (inComment) {
            if (c == '*' && i + 1 < code.length() && code[i + 1] == '/') {
                inComment = false;
                i++;
            }
            continue;
        }
        
        if (c == '/' && i + 1 < code.length()) {
            if (code[i + 1] == '/') break; 
            if (code[i + 1] == '*') {
                inComment = true; 
                i++;
                continue;
            }
        }
        
        if (isspace(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            continue;
        }
        
        if (punctuation.count(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, c));
            continue;
        }
        
        if (operators.count(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, c));
            continue;
        }
        
        if (c == '"') {
            inString = !inString;
        }
        
        if (c == '\\' && i + 1 < code.length() && code[i + 1] == '\"') {
            token += c;
            i++;
        }
        
        token += c;
    }
    
    if (!token.empty()) tokens.push_back(token);
    
    cout << "TOKENS\n";
    for (const string &t : tokens) {
        if (keywords.count(t)) {
            cout << "Keyword: " << t << endl;
        } else if (punctuation.count(t[0])) {
            cout << "Punctuation: " << t << endl;
        } else if (operators.count(t[0])) {
            cout << "Operator: " << t << endl;
        } else if (isConstant(t)) {
            cout << "Constant: " << t << endl;
        } else if (isValidIdentifier(t)) {
            cout << "Identifier: " << t << endl;
            symbolTable.insert(t);
        } else {
            lexicalErrors.push_back(t + " invalid lexeme");
        }
    }
    
    cout << "\nLEXICAL ERRORS\n";
    for (const string &e : lexicalErrors) {
        cout << e << endl;
    }
    
    cout << "\nSYMBOL TABLE ENTRIES\n";
    int index = 1;
    for (const string &id : symbolTable) {
        cout << index++ << ") " << id << endl;
    }
}

int main() {
    // ifstream file("testCase1.c"); 
    ifstream file("testCase2.c"); 
    // ifstream file("testCase3.c"); 
    if (!file) {
        cerr << "Error: Could not open file!" << endl;
        return 1;
    }
    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    
    tokenize(code);
    return 0;
}

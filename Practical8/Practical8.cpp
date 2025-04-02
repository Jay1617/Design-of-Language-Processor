#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
using namespace std;

map<string, vector<string>> grammar = {
    {"S", {"A B C", "D"}},
    {"A", {"a", "ε"}},
    {"B", {"b", "ε"}},
    {"C", {"( S )", "c"}},
    {"D", {"A C"}}
};

map<string, set<string>> first = {
    {"S", {"a", "b", "(", "c"}},
    {"A", {"a", "ε"}},
    {"B", {"b", "ε"}},
    {"C", {"(", "c"}},
    {"D", {"a", "("}}
};

map<string, set<string>> follow = {
    {"S", {")", "$"}},
    {"A", {"b", "(", ")", "$"}},
    {"B", {"c", ")", "$"}},
    {"C", {")", "$"}},
    {"D", {")", "$"}}
};

map<string, map<string, string>> parsing_table;
bool is_ll1 = true;

void constructParsingTable() {
    for (auto &rule : grammar) {
        string non_terminal = rule.first;
        for (string prod : rule.second) {
            set<string> first_set;
            vector<string> symbols;
            size_t pos = 0;
            while ((pos = prod.find(' ')) != string::npos) {
                symbols.push_back(prod.substr(0, pos));
                prod.erase(0, pos + 1);
            }
            symbols.push_back(prod);
            for (string symbol : symbols) {
                if (first.count(symbol)) {
                    first_set.insert(first[symbol].begin(), first[symbol].end());
                    if (first[symbol].find("ε") == first[symbol].end()) break;
                } else {
                    first_set.insert(symbol);
                    break;
                }
            }
            first_set.erase("ε");
            for (string terminal : first_set) {
                if (parsing_table[non_terminal].count(terminal)) is_ll1 = false;
                parsing_table[non_terminal][terminal] = prod;
            }
            if (first[non_terminal].count("ε")) {
                for (string terminal : follow[non_terminal]) {
                    if (parsing_table[non_terminal].count(terminal)) is_ll1 = false;
                    parsing_table[non_terminal][terminal] = "ε";
                }
            }
        }
    }
}

void parseInput(string input) {
    stack<string> stk;
    stk.push("$");
    stk.push("S");
    input += "$";
    int index = 0;
    while (!stk.empty()) {
        string top = stk.top();
        stk.pop();
        char current = input[index];
        if (top == string(1, current)) {
            index++;
        } else if (parsing_table.count(top) && parsing_table[top].count(string(1, current))) {
            string prod = parsing_table[top][string(1, current)];
            if (prod != "ε") {
                vector<string> symbols;
                size_t pos = 0;
                while ((pos = prod.find(' ')) != string::npos) {
                    symbols.push_back(prod.substr(0, pos));
                    prod.erase(0, pos + 1);
                }
                symbols.push_back(prod);
                for (int i = symbols.size() - 1; i >= 0; i--) {
                    stk.push(symbols[i]);
                }
            }
        } else {
            cout << "Invalid string\n";
            return;
        }
    }
    cout << "Valid string\n";
}

int main() {
    constructParsingTable();
    cout << "Predictive Parsing Table:\n";
    for (auto &row : parsing_table) {
        cout << row.first << ": { ";
        for (auto &entry : row.second) {
            cout << entry.first << " -> " << entry.second << " , ";
        }
        cout << "}\n";
    }
    cout << (is_ll1 ? "Grammar is LL(1)\n" : "Grammar is NOT LL(1)\n");
    string input;
    cout << "Enter string to validate: ";
    cin >> input;
    parseInput(input);
    return 0;
}

#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <cctype>
#include <map>
using namespace std;

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isDigit(string s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

string constantFold(string expr) {
    istringstream iss(expr);
    vector<string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    for (int i = 0; i < tokens.size(); i++) {
        if (i + 2 < tokens.size() && isDigit(tokens[i]) && isDigit(tokens[i + 2]) && isOperator(tokens[i + 1][0])) {
            int op1 = stoi(tokens[i]);
            int op2 = stoi(tokens[i + 2]);
            char op = tokens[i + 1][0];
            int res;
            switch (op) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': res = op1 / op2; break;
            }
            tokens[i] = to_string(res);
            tokens.erase(tokens.begin() + i + 1, tokens.begin() + i + 3);
            i = -1;
        }
    }
    
    string optimizedExpr;
    for (const string &t : tokens) {
        optimizedExpr += t + " ";
    }
    return optimizedExpr.substr(0, optimizedExpr.length() - 1);
}

int main() {
    string expr;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expr);
    string optimizedExpr = constantFold(expr);
    cout << "Optimized Expression: " << optimizedExpr << endl;
    return 0;
}

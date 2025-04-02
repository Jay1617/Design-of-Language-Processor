#include <bits/stdc++.h>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isValidChar(char c) {
    return isdigit(c) || isOperator(c) || c == '(' || c == ')' || c == '.' || c == ' ';
}

vector<string> infixToPostfix(string exp) {
    vector<string> output;
    stack<char> ops;
    int i = 0, n = exp.length();
    while (i < n) {
        if (exp[i] == ' ') { i++; continue; }  // Skip spaces
        if (isdigit(exp[i]) || exp[i] == '.') {
            string num;
            while (i < n && (isdigit(exp[i]) || exp[i] == '.')) {
                num += exp[i++];
            }
            output.push_back(num);
            continue;
        } else if (exp[i] == '(') {
            ops.push(exp[i]);
        }
        else if (exp[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                output.push_back(string(1, ops.top()));
                ops.pop();
            }
            if (!ops.empty()) ops.pop();
        } else if (isOperator(exp[i])) {
            while (!ops.empty() && precedence(ops.top()) >= precedence(exp[i])) {
                output.push_back(string(1, ops.top()));
                ops.pop();
            }
            ops.push(exp[i]);
        }
        i++;
    }
    while (!ops.empty()) {
        output.push_back(string(1, ops.top()));
        ops.pop();
    }
    return output;
}

double evaluatePostfix(vector<string>& postfix) {
    stack<double> values;
    for (auto& token : postfix) {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
            values.push(stod(token));
        }
        else {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            if (token == "+") values.push(a + b);
            else if (token == "-") values.push(a - b);
            else if (token == "*") values.push(a * b);
            else if (token == "/") values.push(a / b);
            else if (token == "^") values.push(pow(a, b));
        }
    }
    return values.top();
}

bool isValidExpression(string exp) {
    if (exp.empty()) return false;
    for (char c : exp) if (!isValidChar(c)) return false;
    return true;
}

int main() {
    string exp;
    cout << "Enter an expression: ";
    getline(cin, exp);
    if (!isValidExpression(exp)) {
        cout << "Invalid expression" << endl;
        return 0;
    }
    vector<string> postfix = infixToPostfix(exp);
    cout << evaluatePostfix(postfix) << endl;
    return 0;
}
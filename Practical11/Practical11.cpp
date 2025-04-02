#include <iostream>
#include <stack>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

struct Quadruple {
    string op, arg1, arg2, result;
};

vector<Quadruple> quadruples;
int tempCount = 1;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string generateTemp() {
    return "t" + to_string(tempCount++);
}

void processOperator(stack<string>& operands, stack<char>& operators) {
    string right = operands.top(); operands.pop();
    string left = operands.top(); operands.pop();
    char op = operators.top(); operators.pop();
    string temp = generateTemp();
    quadruples.push_back({string(1, op), left, right, temp});
    operands.push(temp);
}

void generateQuadruples(const string& expression) {
    stack<string> operands;
    stack<char> operators;
    stringstream ss(expression);
    char ch;
    while (ss >> ch) {
        if (isdigit(ch)) {
            string num(1, ch);
            while (ss.peek() != ' ' && isdigit(ss.peek())) {
                num += ss.get();
            }
            operands.push(num);
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                processOperator(operands, operators);
            }
            operators.pop();
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                processOperator(operands, operators);
            }
            operators.push(ch);
        }
    }
    while (!operators.empty()) {
        processOperator(operands, operators);
    }
}

void printQuadruples() {
    cout << "Operator\tOperand1\tOperand2\tResult\n";
    for (const auto& q : quadruples) {
        cout << q.op << "\t\t" << q.arg1 << "\t\t" << q.arg2 << "\t\t" << q.result << "\n";
    }
}

int main() {
    string expression;
    cout << "Enter arithmetic expression: ";
    getline(cin, expression);
    generateQuadruples(expression);
    printQuadruples();
    return 0;
}
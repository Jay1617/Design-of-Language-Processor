#include <iostream>
#include <string>

using namespace std;

string input;
int pos = 0;

bool S();
bool L();
bool LPrime();

bool S() {
    if (pos < input.size() && input[pos] == 'a') { 
        pos++;
        return true;
    } 
    else if (pos < input.size() && input[pos] == '(') { 
        pos++;
        if (L()) {
            if (pos < input.size() && input[pos] == ')') {
                pos++;
                return true;
            }
        }
    }
    return false;
}

bool L() {
    if (S()) {  
        return LPrime();
    }
    return false;
}

bool LPrime() {
    if (pos < input.size() && input[pos] == ',') { 
        pos++;
        if (S()) {
            return LPrime();
        }
        return false;
    }
    return true; 
}

bool isValidString(string str) {
    input = str;
    pos = 0;
    if (S() && pos == input.size()) {
        return true;  
    }
    return false;
}

int main() {
    string testInput;
    cout << "Enter a string: ";
    cin >> testInput;

    if (isValidString(testInput)) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }

    return 0;
}

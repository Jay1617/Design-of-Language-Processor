#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

bool isValid(string symbols, int states, int start, set<int> acceptStates, string input) {
    for (char ch : input) {
        if (symbols.find(ch) == string::npos) {
            return false;
        }
    }

    map<int, map<char, int>> transitions;
    for (int i = 0; i < states; i++) {
        for (char sym : symbols) {
            int nextState;
            cout << "Next state for state " << (i + 1) << " and symbol " << sym << ": ";
            cin >> nextState;
            transitions[i + 1][sym] = nextState;
        }
    }

    int currState = start;
    for (char ch : input) {
        if (transitions[currState].count(ch)) {
            currState = transitions[currState][ch];
        } else {
            return false;
        }
    }

    return acceptStates.count(currState);
}

int main() {
    int symbolsCount, states, start, acceptCount;
    string symbols, input;
    set<int> acceptStates;

    cout << "Number of symbols: ";
    cin >> symbolsCount;
    cout << "Symbols: ";
    cin >> symbols;
    cout << "Number of states: ";
    cin >> states;
    cout << "Start state: ";
    cin >> start;
    cout << "Accepting states count: ";
    cin >> acceptCount;

    cout << "Accepting states: ";
    for (int i = 0; i < acceptCount; i++) {
        int state;
        cin >> state;
        acceptStates.insert(state);
    }

    cout << "Input string: ";
    cin >> input;

    if (isValid(symbols, states, start, acceptStates, input)) {
        cout << "Valid string." << endl;
    } else {
        cout << "Invalid string." << endl;
    }

    return 0;
}

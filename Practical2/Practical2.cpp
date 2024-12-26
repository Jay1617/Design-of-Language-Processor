#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

bool isValid(int noOfSymbol, string inputSymbols, int noOfState, int initialState, set<int> acceptingStates, string inputString) {
    bool checkStringContainInputSymbol = false;

    for (int i = 0; i < inputString.length(); i++) {
        for (int j = 0; j < inputSymbols.length(); j++) {
            if (inputString[i] == inputSymbols[j]) {
                checkStringContainInputSymbol = true;
                break;
            }
        }
        if (!checkStringContainInputSymbol) {
            return false;
        }
        checkStringContainInputSymbol = false;
    }

    map<int, map<char, int>> transitionTable;
    for (int i = 0; i < noOfState; i++) {
        for (int j = 0; j < inputSymbols.length(); j++) {
            int tempState;
            cout << "Enter next state if current state is " << (i + 1) << " and input symbol is " << inputSymbols[j] << ": ";
            cin >> tempState;
            transitionTable[i + 1][inputSymbols[j]] = tempState;
        }
    }

    int currentState = initialState;
    for (int i = 0; i < inputString.length(); i++) {
        char symbol = inputString[i];
        if (transitionTable[currentState].count(symbol)) {
            currentState = transitionTable[currentState][symbol];
        } else {
            return false;
        }
    }

    return acceptingStates.count(currentState);
}

int main() {
    int noOfSymbol, noOfState, initialState, noOfAcceptingStates;
    string inputSymbols, inputString;
    set<int> acceptingStates;

    cout << "Enter number of input symbols: ";
    cin >> noOfSymbol;
    cout << "Enter input symbols: ";
    cin >> inputSymbols;
    cout << "Enter number of states: ";
    cin >> noOfState;
    cout << "Enter initial state: ";
    cin >> initialState;
    cout << "Enter number of accepting states: ";
    cin >> noOfAcceptingStates;
    cout << "Enter accepting states: ";
    for (int i = 0; i < noOfAcceptingStates; i++) {
        int state;
        cin >> state;
        acceptingStates.insert(state);
    }
    cout << "Enter input string: ";
    cin >> inputString;

    if (isValid(noOfSymbol, inputSymbols, noOfState, initialState, acceptingStates, inputString)) {
        cout << "The input string is valid." << endl;
    } else {
        cout << "The input string is invalid." << endl;
    }

    return 0;
}

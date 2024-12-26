//Case : Start and end with same symbol
#include<bits/stdc++.h>
using namespace std;
int main(){

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
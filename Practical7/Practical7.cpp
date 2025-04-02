#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, set<char>> firstSets, followSets;
map<char, vector<string>> productions;
set<char> nonTerminals;
char startSymbol = 'S'; 

void computeFirst(char symbol) {
    if (!nonTerminals.count(symbol)) { 
        firstSets[symbol].insert(symbol);
        return;
    }

    for (string rule : productions[symbol]) {
        bool nullable = true; 

        for (char ch : rule) {
            computeFirst(ch); 
            firstSets[symbol].insert(firstSets[ch].begin(), firstSets[ch].end());

            if (firstSets[ch].count('ε') == 0) {
                nullable = false;
                break;
            }
        }
        if (nullable)
            firstSets[symbol].insert('ε');
    }
}

void computeFollow(char symbol) {
    if (symbol == startSymbol) {
        followSets[symbol].insert('$'); 
    }

    for (auto &prod : productions) {
        char lhs = prod.first;

        for (string rule : prod.second) {
            for (size_t i = 0; i < rule.size(); i++) {
                if (rule[i] == symbol) {
                    bool nullable = true;
                    
                    for (size_t j = i + 1; j < rule.size(); j++) {
                        followSets[symbol].insert(firstSets[rule[j]].begin(), firstSets[rule[j]].end());
                        
                        if (firstSets[rule[j]].count('ε') == 0) {
                            nullable = false;
                            break;
                        }
                    }
                    
                    if (nullable || i == rule.size() - 1) {
                        followSets[symbol].insert(followSets[lhs].begin(), followSets[lhs].end());
                    }
                }
            }
        }
    }
}

void displaySets() {
    for (auto &entry : firstSets) {
        cout << "First(" << entry.first << ") = { ";
        for (char ch : entry.second) {
            cout << ch << " ";
        }
        cout << "}\n";
    }

    cout << "\n";

    for (auto &entry : followSets) {
        cout << "Follow(" << entry.first << ") = { ";
        for (char ch : entry.second) {
            cout << ch << " ";
        }
        cout << "}\n";
    }
}

int main() {
    productions['S'] = {"AB", "C", "D"};
    productions['A'] = {"a", "ε"};
    productions['B'] = {"b", "ε"};
    productions['C'] = {"(S)", "c"};
    productions['D'] = {"AC"};

    for (auto &prod : productions) {
        nonTerminals.insert(prod.first);
    }

    for (char nonTerm : nonTerminals) {
        computeFirst(nonTerm);
    }

    for (char nonTerm : nonTerminals) {
        computeFollow(nonTerm);
    }

    displaySets();

    return 0;
}

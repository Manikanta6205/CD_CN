#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> G;
map<char, set<char>> FIRST, FOLLOW;
map<char, map<char, string>> PARSE_TABLE;
char START;

/* ============== COMPUTE FIRST ============== */
set<char> computeFIRST(char X) {
    // If X is terminal → FIRST(X) = {X}
    if (islower(X))
        return {X};

    if (!FIRST[X].empty())
        return FIRST[X];

    for (string prod : G[X]) {
        if (prod == "#") {
            FIRST[X].insert('#');
            continue;
        }

        for (char Y : prod) {
            set<char> firstY = computeFIRST(Y);

            // Add all except ε
            for (char f : firstY)
                if (f != '#') FIRST[X].insert(f);

            // If FIRST(Y) does not contain ε → stop
            if (!firstY.count('#'))
                break;

            // If FIRST(Y) has ε and Y is last symbol
            if (Y == prod.back())
                FIRST[X].insert('#');
        }
    }
    return FIRST[X];
}

/* ============== COMPUTE FOLLOW ============== */
void computeFOLLOW(char X) {
    if (X == START)
        FOLLOW[X].insert('$');  // Add end marker for start symbol

    for (auto p : G) {
        char A = p.first;
        for (string rhs : p.second) {
            for (int i = 0; i < rhs.size(); i++) {
                if (rhs[i] == X) {
                    if (i + 1 < rhs.size() && islower(rhs[i + 1]))
                        FOLLOW[X].insert(rhs[i + 1]);

                    else if (i + 1 < rhs.size() && isupper(rhs[i + 1])) {
                        for (char f : FIRST[rhs[i + 1]])
                            if (f != '#') FOLLOW[X].insert(f);

                        if (FIRST[rhs[i + 1]].count('#'))
                            FOLLOW[X].insert(FOLLOW[A].begin(), FOLLOW[A].end());
                    }

                    else if (i + 1 == rhs.size() && X != A) {
                        FOLLOW[X].insert(FOLLOW[A].begin(), FOLLOW[A].end());
                    }
                }
            }
        }
    }
}

/* ============== BUILD PARSE TABLE ============== */
void buildParseTable() {
    for (auto p : G) {
        char A = p.first;
        for (string prod : p.second) {
            set<char> firstSet;

            if (prod == "#")
                firstSet.insert('#');
            else {
                for (char ch : prod) {
                    set<char> f = computeFIRST(ch);
                    firstSet.insert(f.begin(), f.end());
                    if (!f.count('#')) break;
                }
            }

            for (char t : firstSet)
                if (t != '#')
                    PARSE_TABLE[A][t] = string(1, A) + "->" + prod;

            if (firstSet.count('#'))
                for (char b : FOLLOW[A])
                    PARSE_TABLE[A][b] = string(1, A) + "->" + prod;
        }
    }
}

/* ============== MAIN ============== */
int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (use # for ε). Example input:\n";
    cout << "E->TR\nR->+TR|#\nT->FY\nY->*FY|#\nF->(E)|i\n\n";

    for (int i = 0; i < n; i++) {
        string rule;
        cin >> rule;
        char lhs = rule[0];
        if (i == 0) START = lhs;

        string rhs = "";
        for (int j = 3; j < rule.size(); j++) {
            if (rule[j] == '|') {
                G[lhs].push_back(rhs);
                rhs = "";
            } else rhs += rule[j];
        }
        G[lhs].push_back(rhs);
    }

    for (auto p : G) computeFIRST(p.first);
    for (auto p : G) computeFOLLOW(p.first);

    cout << "\nFIRST Sets:\n";
    for (auto p : FIRST) {
        cout << "FIRST(" << p.first << ") = { ";
        for (char c : p.second) cout << c << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW Sets:\n";
    for (auto p : FOLLOW) {
        cout << "FOLLOW(" << p.first << ") = { ";
        for (char c : p.second) cout << c << " ";
        cout << "}\n";
    }

    buildParseTable();

    cout << "\nLL(1) PARSE TABLE:\n";
    for (auto p : PARSE_TABLE) {
        for (auto q : p.second)
            cout << p.first << " , " << q.first << " → " << q.second << endl;
    }

    return 0;
}

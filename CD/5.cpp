#include <bits/stdc++.h>
using namespace std;

// ---------------- BNF to YACC -----------------
map<string, string> bnf_to_yacc(string bnf) {
    map<string, string> rules;
    stringstream ss(bnf);
    string line;
    while (getline(ss, line)) {
        if (line.find("::=") == string::npos) continue;
        string left = line.substr(0, line.find("::="));
        string right = line.substr(line.find("::=") + 3);
        left.erase(remove_if(left.begin(), left.end(), ::isspace), left.end());
        rules[left] = right;
    }
    return rules;
}

// ---------------- Minimal Parsing ----------------
string expr;
int posn = 0;

char peekc() {
    while (posn < expr.size() && isspace(expr[posn])) posn++;
    if (posn < expr.size()) return expr[posn];
    return '\0';
}

char getc() {
    char c = peekc();
    posn++;
    return c;
}

vector<string> val;
vector<int> L, R;

int makeNode(string v, int l = -1, int r = -1) {
    val.push_back(v);
    L.push_back(l);
    R.push_back(r);
    return val.size() - 1;
}


int number() {
    string num;
    while (isdigit(peekc())) num += getc();
    return makeNode(num);
}

int term() {
    int node = number();
    while (peekc() == '*' || peekc() == '/') {
        char op = getc();
        int right = number();
        node = makeNode(string(1, op), node, right);
    }
    return node;
}

int expression() {
    int node = term();
    while (peekc() == '+' || peekc() == '-') {
        char op = getc();
        int right = term();
        node = makeNode(string(1, op), node, right);
    }
    return node;
}

void printAST(int idx, int level) {
    if (idx == -1) return;
    for (int i = 0; i < level; i++) 
        cout << "  ";
    cout << val[idx] << "\n";
    printAST(L[idx], level + 1);
    printAST(R[idx], level + 1);
}

int main() {
    cout << "Enter BNF grammar (end with empty line):\n";
    string bnf_line, bnf;
    while (true) {
        getline(cin, bnf_line);
        if (bnf_line.empty()) break;
        bnf += bnf_line + "\n";
    }

    auto yacc_rules = bnf_to_yacc(bnf);
    cout << "\nConverted YACC-like rules:\n";
    for (auto &r : yacc_rules) {
        cout << r.first << " : " << r.second << "\n";
    }

    cout << "\nEnter arithmetic expression:\n";
    getline(cin, expr);
    posn = 0;

    int root = expression();

    cout << "\nAbstract Syntax Tree:\n";
    printAST(root, 0);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

struct ThreeAC { 
    string op, arg1, arg2, result; 
};

string getRegister(string var, unordered_map<string, string>& regMap, int& regCount) { 
    if (regMap.find(var) == regMap.end()) 
        regMap[var] = "R" + to_string(regCount++); 
    return regMap[var]; 
}

int main() { 
    int n;
    cout << "Enter number of 3-address code statements: ";
    cin >> n;
    cin.ignore();

    vector<ThreeAC> code(n);
    cout << "Enter each 3-address code statement (e.g., t1 = a + b):\n";

    for (int i = 0; i < n; ++i) { 
        cout << "Statement " << i + 1 << ": ";
        string line; 
        getline(cin, line);
        stringstream ss(line); 
        string eq;
        ss >> code[i].result >> eq >> code[i].arg1 >> code[i].op >> code[i].arg2;
        if (code[i].op.empty()) 
            code[i].op = "="; 
    }

    cout << "\nGenerated Assembly Code:\n";

    unordered_map<string, string> regMap;
    int regCount = 0;

    for (auto &stmt : code) { 
        string r1 = getRegister(stmt.arg1, regMap, regCount); 
        string r2 = getRegister(stmt.arg2, regMap, regCount); 
        string r3 = getRegister(stmt.result, regMap, regCount); 

        if (stmt.op == "+") 
            cout << "MOV " << r3 << ", " << r1 << "\nADD " << r3 << ", " << r2 << "\n";
        else if (stmt.op == "-") 
            cout << "MOV " << r3 << ", " << r1 << "\nSUB " << r3 << ", " << r2 << "\n";
        else if (stmt.op == "*") 
            cout << "MOV " << r3 << ", " << r1 << "\nMUL " << r3 << ", " << r2 << "\n";
        else if (stmt.op == "/") 
            cout << "MOV " << r3 << ", " << r1 << "\nDIV " << r3 << ", " << r2 << "\n";
        else if (stmt.op == "=") 
            cout << "MOV " << r3 << ", " << r1 << "\n";
    }
}
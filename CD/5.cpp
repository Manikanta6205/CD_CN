#include <bits/stdc++.h>
using namespace std;
map<string,string>bnfy(string bnf){
    map<string,string>rules;stringstream ss(bnf);string line;
    while(getline(ss,line)){
        if(line.find("::=")==string::npos)continue;
        string left=line.substr(0,line.find("::="));
        string right=line.substr(line.find("::=")+3);
        rules[left]=right;
    }
    return rules;
}
string expr;
int posn=0;
char peekc(){
    while(posn<expr.size()&&iss

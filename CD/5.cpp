#include <bits/stdc++.h>
using namespace std;
string expr;
int posn=0;
char peekc(){
    while(posn<expr.size()&&isspace(expr[posn]))posn++;
    if(posn<expr.size())return expr[posn];
    return '\0';
}
char getc(){
    char c=peekc();
    posn++;
    return c;
}
vector<string> val;
vector<int> L,R;
int makeNode(string v,int l=-1,int r=-1){
    val.push_back(v);
    L.push_back(l);
    R.push_back(r);
    return val.size()-1;
}
int number(){
    string num;
    while(isdigit(peekc()))num+=getc();
    return makeNode(num);
}
int term(){
    int node=number();
    while(peekc()=='*'||peekc()=='/'){
        char op=getc();
        int right=number();
        node=makeNode(string(1,op),node,right);
    }
    return node;
}
int expression(){
    int node=term();
    while(peekc()=='+'||peekc()=='-'){
        char op=getc();
        int right=term();
        node=makeNode(string(1,op),node,right);
    }
    return node;
}
void printAST(int idx,int level){
    if(idx==-1)return;
    for(int i=0;i<level;i++)
        cout<<"  ";
    cout<<val[idx]<<"\n";
    printAST(L[idx],level+1);
    printAST(R[idx],level+1);
}
int main(){
    string s;
    cout<<"Enter grammar rules (empty line to end):\n";
    while(true){
        getline(cin,s);
        if(s.empty())break;
        int p=s.find("::=");
        for(int i=0;i<p;i++)cout<<s[i];
        cout<<" : ";
        for(int i=3+p;i<s.size();i++)cout<<s[i];
        cout<<"\n";
    }
    cout<<"\nEnter arithmetic expression:\n";
    getline(cin,expr);
    int root=expression();
    cout<<"\nAbstract Syntax Tree:\n";
    printAST(root,0);
    return 0;
}

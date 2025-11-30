#include <bits/stdc++.h>
using namespace std;
map<char,vector<string>>G;
map<char,set<char>>FIRST,FOLLOW;
map<char,map<char,string>>PTBL;
char START;
set<char>cFST(char X){
    if(islower(X))return{X};
    if(!FIRST[X].empty())return FIRST[X];
    for(string prod:G[X]){
        if(prod=="#"){FIRST[X].insert('#');continue;}
        for(char Y:prod){
            set<char>firstY=cFST(Y);
            for(char f:firstY)if(f!='#')FIRST[X].insert(f);
            if(!firstY.count('#'))break;
            if(Y==prod.back())FIRST[X].insert('#');
        }
    }
    return FIRST[X];
}
void cFLW(char X){
    if(X==START)FOLLOW[X].insert('$');
    for(auto p:G){
        char A=p.first;
        for(string rhs:p.second){
            for(int i=0;i<rhs.size();i++){
                if(rhs[i]==X){
                    if(i+1<rhs.size()&&islower(rhs[i+1]))FOLLOW[X].insert(rhs[i+1]);
                    else if(i+1<rhs.size()&&isupper(rhs[i+1])){
                        for(char f:FIRST[rhs[i+1]])if(f!='#')FOLLOW[X].insert(f);
                        if(FIRST[rhs[i+1]].count('#'))FOLLOW[X].insert(FOLLOW[A].begin(),FOLLOW[A].end());
                    }
                    else if(i+1==rhs.size()&&X!=A)FOLLOW[X].insert(FOLLOW[A].begin(),FOLLOW[A].end());
                }
            }
        }
    }
}
void bTAB(){
    for(auto p:G){
        char A=p.first;
        for(string prod:p.second){
            set<char>fset;
            if(prod=="#")fset.insert('#');
            else{
                for(char ch:prod){
                    set<char>f=cFST(ch);
                    fset.insert(f.begin(),f.end());
                    if(!f.count('#'))break;
                }
            }
            for(char t:fset)if(t!='#')PTBL[A][t]=string(1,A)+"->"+prod;
            if(fset.count('#'))for(char b:FOLLOW[A])PTBL[A][b]=string(1,A)+"->"+prod;
        }
    }
}
int main(){
    int n;
    cout<<"Enter number of productions: ";
    cin>>n;
    cout<<"Enter productions (use # for ε). Example input:\n";
    cout<<"E->TR\nR->+TR|#\nT->FY\nY->*FY|#\nF->(E)|i\n\n";
    for(int i=0;i<n;i++){
        string rule;
        cin>>rule;
        char lhs=rule[0];
        if(i==0)START=lhs;
        string rhs="";
        for(int j=3;j<rule.size();j++){
            if(rule[j]=='|'){G[lhs].push_back(rhs);rhs="";}
            else rhs+=rule[j];
        }
        G[lhs].push_back(rhs);
    }
    for(auto p:G)cFST(p.first);
    for(auto p:G)cFLW(p.first);
    cout<<"\nFIRST Sets:\n";
    for(auto p:FIRST){
        cout<<"FIRST("<<p.first<<") = { ";
        for(char c:p.second)cout<<c<<" ";
        cout<<"}\n";
    }
    cout<<"\nFOLLOW Sets:\n";
    for(auto p:FOLLOW){
        cout<<"FOLLOW("<<p.first<<") = { ";
        for(char c:p.second)cout<<c<<" ";
        cout<<"}\n";
    }
    bTAB();
    cout<<"\nLL(1) PARSE TABLE:\n";
    for(auto p:PTBL){
        for(auto q:p.second)cout<<p.first<<" , "<<q.first<<" → "<<q.second<<endl;
    }
    return 0;
}

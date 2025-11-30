#include <bits/stdc++.h>
using namespace std;
struct ThreeAC{string op,arg1,arg2,result;};
string gReg(string v,unordered_map<string,string>& rmap,int& rcnt){if(rmap.find(v)==rmap.end())rmap[v]="R"+to_string(rcnt++);return rmap[v];}
int main(){
    int n;cout<<"Enter number of 3-address code statements: ";cin>>n;cin.ignore();
    vector<ThreeAC>code(n);cout<<"Enter each 3-address code statement (e.g., t1 = a + b):\n";
    for(int i=0;i<n;++i){cout<<"Statement "<<i+1<<": ";string line;getline(cin,line);stringstream ss(line);string eq;ss>>code[i].result>>eq>>code[i].arg1>>code[i].op>>code[i].arg2;if(code[i].op.empty())code[i].op="=";}
    cout<<"\nGenerated Assembly Code:\n";
    unordered_map<string,string>rmap;int rcnt=0;
    for(auto &st:code){
        string r1=gReg(st.arg1,rmap,rcnt);string r2=gReg(st.arg2,rmap,rcnt);string r3=gReg(st.result,rmap,rcnt);
        if(st.op=="+")cout<<"MOV "<<r3<<", "<<r1<<"\nADD "<<r3<<", "<<r2<<"\n";
        else if(st.op=="-")cout<<"MOV "<<r3<<", "<<r1<<"\nSUB "<<r3<<", "<<r2<<"\n";
        else if(st.op=="*")cout<<"MOV "<<r3<<", "<<r1<<"\nMUL "<<r3<<", "<<r2<<"\n";
        else if(st.op=="/")cout<<"MOV "<<r3<<", "<<r1<<"\nDIV "<<r3<<", "<<r2<<"\n";
        else if(st.op=="=")cout<<"MOV "<<r3<<", "<<r1<<"\n";
    }
    return 0;
}

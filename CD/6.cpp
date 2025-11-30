#include <bits/stdc++.h>
using namespace std;
vector<string>tokn(string s){
    vector<string>tkns;string tmp="";
    for(int i=0;i<s.size();i++){
        if(isalnum(s[i])||s[i]=='_')tmp+=s[i];
        else{
            if(!tmp.empty()){tkns.push_back(tmp);tmp="";}
            if(s[i]==' ')continue;
            tkns.push_back(string(1,s[i]));
        }
    }
    if(!tmp.empty())tkns.push_back(tmp);
    return tkns;
}
int prec(string op){
    if(op=="+"||op=="-")return 1;
    else if(op=="*"||op=="/")return 2;
    return 0;
}
vector<string>i2pf(vector<string>tkns){
    vector<string>out;stack<string>st;
    for(auto x:tkns){
        if(isalnum(x[0])||x[0]=='_')out.push_back(x);
        else if(x=="(")st.push(x);
        else if(x==")"){
            while(!st.empty()&&st.top()!="("){
                out.push_back(st.top());st.pop();
            }
            st.pop();
        }
        else{
            while(!st.empty()&&st.top()!="("&&prec(st.top())>=prec(x)){
                out.push_back(st.top());st.pop();
            }
            st.push(x);
        }
    }
    while(!st.empty()){out.push_back(st.top());st.pop();}
    return out;
}
void gTAC(vector<string>pf){
    vector<tuple<string,string,string,string>>quad;
    vector<tuple<string,string,string>>trip;
    stack<string>st;int tct=1;
    for(auto x:pf){
        if(isalnum(x[0])||x[0]=='_')st.push(x);
        else{
            string b=st.top();st.pop();
            string a=st.top();st.pop();
            string tmp="t"+to_string(tct++);
            quad.push_back({x,a,b,tmp});
            auto conv=[&](string s){return(s[0]=='t')?"(" + to_string(stoi(s.substr(1))-1) + ")":s;};
            trip.push_back({x,conv(a),conv(b)});
            st.push(tmp);
        }
    }
    cout<<"\nQuadruples:\nIdx\tOp\tArg1\tArg2\tResult\n";
    for(int i=0;i<quad.size();i++){
        auto[op,a,b,r]=quad[i];
        cout<<i<<"\t"<<op<<"\t"<<a<<"\t"<<b<<"\t"<<r<<"\n";
    }
    cout<<"\nTriples:\nIdx\tOp\tArg1\tArg2\n";
    for(int i=0;i<trip.size();i++){
        auto[op,a,b]=trip[i];
        cout<<i<<"\t"<<op<<"\t"<<a<<"\t"<<b<<"\n";
    }
    cout<<"\nIndirect Triples:\nIdx\tPointer\n";
    for(int i=0;i<trip.size();i++)cout<<i<<"\t("<<i<<")\n";
}
int main(){
    string expr;cout<<"Enter expression: ";getline(cin,expr);
    auto tkns=tokn(expr);
    auto pf=i2pf(tkns);
    gTAC(pf);
    return 0;
}

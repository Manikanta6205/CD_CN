#include <bits/stdc++.h>
using namespace std;
const regex kwpt(R"(\b(?:auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while|main|namespace|public|private|protected|class|friend|virtual|template|this|new|delete|try|catch|throw|inline|using|export|mutable)\b)");
const regex oppt(R"([+\-*/%=<>!&|^~]|<<|>>|::)");
const regex sppt(R"([{}();,.\[\]])");
const regex dtpt(R"(\b(?:int|float|double|char|long|short|void|bool|unsigned)\s+([A-Za-z_][A-Za-z0-9_]*)\b)");
void rmcm(string &cont){
    size_t pos;
    while((pos=cont.find("//"))!=string::npos){
        size_t end_pos=cont.find("\n",pos);
        if(end_pos==string::npos)end_pos=cont.size();
        cont.erase(pos,end_pos-pos);
    }
    while((pos=cont.find("/*"))!=string::npos){
        size_t end_pos=cont.find("*/",pos);
        if(end_pos==string::npos)break;
        cont.erase(pos,end_pos-pos+2);
    }
}
void ancp(const string &fpth){
    ifstream f(fpth);
    if(!f.is_open()){cerr<<"Error: Could not open file: "<<fpth<<endl;return;}
    string cont((istreambuf_iterator<char>(f)),istreambuf_iterator<char>());
    f.close();
    rmcm(cont);
    set<string> kws;
    sregex_iterator wbeg(cont.begin(),cont.end(),kwpt), wend;
    for(sregex_iterator it=wbeg; it!=wend; ++it) kws.insert(it->str());
    set<string> ids;
    wbeg = sregex_iterator(cont.begin(),cont.end(),dtpt);
    for(sregex_iterator it=wbeg; it!=wend; ++it) ids.insert(it->str(1));
    for(const auto &k:kws) ids.erase(k);
    vector<string> ops;
    wbeg = sregex_iterator(cont.begin(),cont.end(),oppt);
    for(sregex_iterator it=wbeg; it!=wend; ++it) ops.push_back(it->str());
    vector<string> sps;
    wbeg = sregex_iterator(cont.begin(),cont.end(),sppt);
    for(sregex_iterator it=wbeg; it!=wend; ++it) sps.push_back(it->str());
    cout<<"=== C/C++ Program Lexical Analysis ===\n\n";
    cout<<"Keywords found ("<<kws.size()<<"):\n";
    for(const auto &k:kws) cout<<k<<" ";
    cout<<"\n\nIdentifiers found ("<<ids.size()<<"):\n";
    for(const auto &id:ids) cout<<id<<" ";
    cout<<"\n\nOperators found ("<<ops.size()<<"):\n";
    for(const auto &op:ops) cout<<op<<" ";
    cout<<"\n\nSpecial symbols found ("<<sps.size()<<"):\n";
    for(const auto &sym:sps) cout<<sym<<" ";
    cout<<"\n";
}
int main(){
    string fpth="sample.c";
    ancp(fpth);
    return 0;
}

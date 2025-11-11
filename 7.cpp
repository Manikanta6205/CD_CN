#include <bits/stdc++.h>
using namespace std;

string getRegister(string v, map<string,string>& reg, int& rc) {
	if(!reg.count(v))
		reg[v] = "R" + to_string(rc++);
	return reg[v];
}

int main() {
	int n;
	cout << "Enter number of 3-address code statements: ";
	cin >> n; cin.ignore();
	cout << "Enter each 3-address code statement (e.g., t1 = a + b):\n";

	struct S { string res, op, a1, a2; };
	vector<S> st(n);

	auto addSpaces=[&](string s){
		string t;
		for(char c:s){
			if(strchr("=+-*/",c)) t+=' ',t+=c,t+=' ';
			else t+=c;
		}
		return t;
	};

	for(int i=0;i<n;i++){
		cout<<"Statement "<<i+1<<": ";
		string line; getline(cin,line);
		line=addSpaces(line);
		string eq; stringstream ss(line);
		ss>>st[i].res>>eq>>st[i].a1>>st[i].op>>st[i].a2;
		if(st[i].op.empty()) st[i].op="=";
	}

	cout<<"\nGenerated Assembly Code:\n";
	map<string,string> reg; int rc=1;

	for(auto &x:st){
		string r1=getRegister(x.a1,reg,rc), r2=getRegister(x.a2,reg,rc), r3=getRegister(x.res,reg,rc);

		if(x.op=="+"){
			cout<<"MOV "<<r3<<", "<<x.a1<<"\n";
			cout<<"ADD "<<r3<<", "<<x.a2<<"\n";
		}
		else if(x.op=="-"){
			cout<<"MOV "<<r3<<", "<<x.a1<<"\n";
			cout<<"SUB "<<r3<<", "<<x.a2<<"\n";
		}
		else if(x.op=="*"){
			cout<<"MOV "<<r3<<", "<<x.a1<<"\n";
			cout<<"MUL "<<r3<<", "<<x.a2<<"\n";
		}
		else if(x.op=="/"){
			cout<<"MOV "<<r3<<", "<<x.a1<<"\n";
			cout<<"DIV "<<r3<<", "<<x.a2<<"\n";
		}
		else cout<<"MOV "<<r3<<", "<<x.a1<<"\n";
		
		cout<<"MOV "<<x.res<<", "<<r3<<"\n";
	}
}

#include <iostream>
using namespace std;
string addB(string a,string b){
    string res="";int cr=0;
    for(int i=a.size()-1;i>=0;i--){
        int b1=a[i]-'0';
        int b2=b[i]-'0';
        int s=b1+b2+cr;
        res=char((s%2)+'0')+res;
        cr=s/2;
    }
    if(cr==1){
        string one=string(a.size()-1,'0')+"1";
        return addB(res,one);
    }
    return res;
}
string oneC(string s){
    for(int i=0;i<s.size();i++)s[i]=(s[i]=='0')?'1':'0';
    return s;
}
int main(){
    int n;cout<<"Enter number of 8-bit blocks: ";cin>>n;
    string data[100];
    cout<<"Enter each 8-bit binary block:\n";
    for(int i=0;i<n;i++)cin>>data[i];
    string sum=data[0];
    for(int i=1;i<n;i++)sum=addB(sum,data[i]);
    string chks=oneC(sum);
    cout<<"\n--- SENDER SIDE ---\n";
    cout<<"Final Sum:   "<<sum<<endl;
    cout<<"Checksum:    "<<chks<<endl;
    cout<<"\nEnter received blocks (including checksum):\n";
    string recv[100];
    for(int i=0;i<n+1;i++)cin>>recv[i];
    string rsum=recv[0];
    for(int i=1;i<n+1;i++)rsum=addB(rsum,recv[i]);
    string fchk=oneC(rsum);
    cout<<"\n--- RECEIVER SIDE ---\n";
    if(fchk==string(fchk.size(),'0'))cout<<"Status: No Error (Data is correct)\n";
    else cout<<"Status: ERROR detected (Data corrupted)\n";
    return 0;
}

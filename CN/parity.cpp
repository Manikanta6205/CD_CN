#include <iostream>
using namespace std;

int cnt1(string s){
    int c=0;
    for(char x:s){
        if(x=='1')c++;
    }
    return c;
}

int main(){
    string data;
    int ch;
    cout<<"Enter binary string: ";
    cin>>data;
    cout<<"Choose Parity Type:\n";
    cout<<"1. Even Parity\n";
    cout<<"2. Odd Parity\n";
    cin>>ch;
    int ones=cnt1(data);
    char pbit;
    if(ch==1){
        if(ones%2==0)pbit='0';
        else pbit='1';
    }else if(ch==2){
        if(ones%2==0)pbit='1';
        else pbit='0';
    }
    string trns=data+pbit;
    cout<<"\n--- SENDER SIDE ---\n";
    cout<<"Original Data:   "<<data<<endl;
    cout<<"Parity Bit:      "<<pbit<<endl;
    cout<<"Transmitted Data: "<<trns<<endl;
    string recv;
    cout<<"\nEnter received binary string: ";
    cin>>recv;
    int rc1=cnt1(recv);
    bool corr;
    if(ch==1)corr=(rc1%2==0);
    else corr=(rc1%2==1);
    cout<<"\n--- RECEIVER SIDE ---\n";
    if(corr)cout<<"Status: No Error (Data is correct)\n";
    else cout<<"Status: ERROR detected (Data corrupted)\n";
    return 0;
}

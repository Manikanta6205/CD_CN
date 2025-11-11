#include<bits/stdc++.h> 
using namespace std; 
int main() { 
    int fs, c = 0; 
    string s; 
    cout << "Enter Packet : "; 
    cin >> s; 
    cout << "Enter Frame size : "; 
    cin >> fs; 
    vector<string> vs; 
    string ss = "", flag = "01111110"; 
    for (int i = 0; i < s.size(); i++) { 
        if (ss.size() == fs) { 
            vs.push_back(ss); 
            ss = ""; 
            c = 0; 
        } 
        if (c == 5) { 
            ss += '0'; 
            c = 0; 
            i--; 
            continue; 
        } 
        if (s[i] == '1') { 
            ss += '1'; 
            c++; 
        } else { 
            ss += '0'; 
            c = 0; 
        } 
    } 
    vs.push_back(ss); 

    cout << "Frames:" << endl; 
    for (int i = 0; i < vs.size(); i++) { 
        string frame = flag + vs[i] + flag; 
        cout << "Frame " << i + 1 << ": " << frame << endl; 
    } 
    cout << endl; 
    
    string ds = ""; 
    for (int i = 0; i < vs.size(); i++) { 
        string chunk = vs[i]; 
        c = 0; 
        for (int j = 0; j < chunk.size(); j++) { 
            char y = chunk[j]; 
            if (y == '1') { 
                c++; 
                ds += '1'; 
            } else { 
                if (c == 5) { 
                    c = 0; 
                    continue; 
                } 
                ds += '0'; 
                c = 0; 
            } 
        } 
    } 
    cout << "De-stuffed String:" << endl; 
    cout << ds << endl; 
    return 0; 
}

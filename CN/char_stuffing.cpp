#include <bits/stdc++.h> 
using namespace std; 
int main() { 
    string s; 
    cout << "Enter String:" << endl; 
    cin >> s; 
    string ss = ""; 

    for (int i = 0; i < s.size(); ) { 
        if (i + 4 <= s.size() && s.substr(i, 4) == "flag") { 
            ss += "esc"; 
            ss += "flag"; 
            i += 4; 
        } 
        else if (i + 3 <= s.size() && s.substr(i, 3) == "esc") { 
            ss += "esc"; 
            ss += "esc"; 
            i += 3; 
        } 
        else { 
            ss += s[i]; 
            i++; 
        } 
    } 
    cout << "Stuffed String: flag" << ss << "flag" << endl; 

    string ds = ""; 
    for (int i = 0; i < ss.size(); ) { 
        if (i + 3 <= ss.size() && ss.substr(i, 3) == "esc") { 
            if (i + 7 <= ss.size() && ss.substr(i + 3, 4) == "flag") { 
                ds += "flag"; 
                i += 7;   
            } 
            else if (i + 6 <= ss.size() && ss.substr(i + 3, 3) == "esc") { 
                ds += "esc"; 
                i += 6; 
            } 
            else { 
                ds += ss[i]; 
                i++; 
            } 
        } 
        else { 
            ds += ss[i]; 
            i++; 
        } 
    } 
    cout << "De-stuffed String:\n" << ds << endl; 
    return 0; 
} 

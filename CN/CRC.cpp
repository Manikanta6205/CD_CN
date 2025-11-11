#include <bits/stdc++.h>
using namespace std;

string xr(string a, string b) {
    string r = "";
    for (int i = 1; i < b.size(); i++)
        r += (a[i] == b[i] ? '0' : '1');
    return r;
}

string div2(string dv, string dr) {
    int n = dr.size();
    string t = dv.substr(0, n);

    int i = n;
    while (i < dv.size()) {
        if (t[0] == '1')
            t = xr(dr, t) + dv[i];
        else
            t = t.substr(1) + dv[i];
        i++;
    }

    if (t[0] == '1')
        t = xr(dr, t);
    else
        t = t.substr(1);

    return t;
}

string enc(string d, string k) {
    string ap = d + string(k.size() - 1, '0');
    string r = div2(ap, k);
    return d + r;
}

int main() {
    string d, k;
    cout << "dataword: ";
    cin >> d;
    cout << "divisor: ";
    cin >> k;

    string cw = enc(d, k);
    cout << "Codeword: " << cw << "\n";

    string rc;
    cout << "received codeword: ";
    cin >> rc;

    string r = div2(rc, k);

    if (r.find('1') != string::npos)
        cout << "Error!\n";
    else
        cout << "OK\n";

    return 0;
}

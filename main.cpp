#include <bits/stdc++.h>
using namespace std;
  
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector <int> a_pref(n+2, 0);
    vector <int> c_suf(n+2, 0);
    vector <int> b;
    for (int i = 1; i <= n; i++) {
        a_pref[i] = a_pref[i-1] + (s[i-1] == 'a');
        if (s[i-1] == 'b') {
            b.push_back(i);
        }
    }
    for (int i = n; i > 0; i--) {
        c_suf[i] = c_suf[i+1] + (s[i-1] == 'c');
    }
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        auto iterator_l = lower_bound(b.begin(), b.end(), l);
        auto iterator_r = upper_bound(b.begin(), b.end(), r);
        if (iterator_r == iterator_l) {
            cout << 0 << endl;
            continue;
        }
        int ans = 0;
        int b_l = iterator_l - b.begin();
        int b_r = iterator_r - b.begin() - 1;
        while (b_r - b_l > 10) {
            int mid1 = b_l + (b_r - b_l) / 3;
            int mid2 = b_r - (b_r - b_l) / 3;
            
            int pos1 = b[mid1];
            int a1 = a_pref[pos1-1] - a_pref[l-1];
            int c1 = c_suf[pos1+1] - c_suf[r+1];
            int val1 = min(a1, c1);
            
            int pos2 = b[mid2];
            int a2 = a_pref[pos2-1] - a_pref[l-1];
            int c2 = c_suf[pos2+1] - c_suf[r+1];
            int val2 = min(a2, c2);
            
            if (val1 < val2) {
                b_l = mid1;
            } else {
                b_r = mid2;
            }
        }
        for (int i = b_l; i <= b_r; i++) {
            int pos = b[i];
            int a_count = a_pref[pos-1] - a_pref[l-1];
            int c_count = c_suf[pos+1] - c_suf[r+1];
            ans = max(ans, min(a_count, c_count));
        }
        cout << 2*ans + 1 << endl;
    }
}

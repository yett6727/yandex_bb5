#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

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

    while (q--){
        int l, r;
        cin >> l >> r;

        int l_it = l;
        int r_it = r;

        if (lower_bound(b.begin(), b.end(), l_it) == upper_bound(b.begin(), b.end(), r_it)){
            cout << 0 << endl;
            continue;
        }
        
        while (l_it < r_it){
            int mid = (r_it + l_it) / 2;

            int a_it = lower_bound(a_pref.begin() + l_it, a_pref.end(), mid + a_pref[l_it - 1]) - a_pref.begin();
            if (a_it >= r_it){
                r_it = mid;
                continue;
            }

            int b_it = lower_bound(b.begin(), b.end(), a_it) - b.begin();
            if(b_it == b.size()) continue;
            if(b[b_it] > r_it){
                r_it = mid;
                continue;
            }

            if(c_suf[b_it] - c_suf[r_it + 1] < mid) l_it = mid;
            else r_it = mid;
        }

        cout << 2 * l_it + 1 << endl;
    }
}
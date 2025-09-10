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

            int left_a = l;
            int right_a = r;
            int a_pos = r + 1;
            
            while (left_a <= right_a) {
                int mid_a = (left_a + right_a) / 2;
                if (a_pref[mid_a] - a_pref[l-1] >= mid) {
                    a_pos = mid_a;
                    right_a = mid_a - 1;
                } else {
                    left_a = mid_a + 1;
                }
            }
            
            if (a_pos > r) {
                r_it = mid - 1;
                continue;
            }

            auto b_it = lower_bound(b.begin(), b.end(), a_pos);
            if (b_it == b.end() || *b_it > r) {
                r_it = mid - 1;
                continue;
            }
            int b_pos_val = *b_it;

            int c_needed = mid;
            int actual_c = c_suf[b_pos_val + 1] - c_suf[r + 1];
            
            if (actual_c >= c_needed) {
                l_it = mid + 1;
            } else {
                r_it = mid - 1;
            };
        }

        cout << 2 * (l_it - 1) + 1 << endl;
    }
}
#include <bits/stdc++.h>
using namespace std;

int findMin(const std::vector<int>& arr, vector <int>& a_pref, vector <int>& c_suf, int l, int r, vector <int> b){
    while (l < r) {
        int d = abs(a_pref[b[l]-1] - c_suf[b[r]+1]);

        int mid = l + (r - l) / 2;
        if (arr[mid] - d > arr[mid + 1] - d) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return l;
}

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

    vector <int> arr(b.size());
    
    for (int i = 0; i < b.size(); i++){
        arr[i] = abs(a_pref[b[i]] - c_suf[b[i]]);
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

        int b_l = iterator_l - b.begin();
        int b_r = iterator_r - b.begin() - 1;

        int ans = findMin(arr, a_pref, c_suf, b_l, b_r, b);
        cout << 2*(a_pref[ans] - a_pref[b_l]) + 1 << endl;
    }
}

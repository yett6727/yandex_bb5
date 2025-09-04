#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    
    vector <int> prefa(n + 1, 0), prefc(n + 1, 0);
    vector <int> posb;
    
    for (int i = 0; i < n; i++){
        prefa[i + 1] = prefa[i] + (s[i] == 'a');
        prefc[i + 1] = prefc[i] + (s[i] == 'c');

        if (s[i] == 'b') posb.push_back(i);
    }
    
    while (q--){
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        
        /*if (prefb[r + 1] - prefb[l] == 0) { //performs similar check to the next 'if', completely rudimentary
            cout << 0 << endl;
            continue;
        }*/
        
        auto it_first = lower_bound(posb.begin(), posb.end(), l);
        auto it_last = upper_bound(posb.begin(), posb.end(), r);
        if (it_first == it_last) {
            cout << 0 << endl;
            continue;
        }

        int best_result = 0;
        
        for (auto it = it_first; it != it_last; it++) {
            int b_pos = *it;

            int a_left = prefa[b_pos + 1] - prefa[l];
            int c_right = prefc[r + 1] - prefc[b_pos + 1];

            int left_k = 0;
            int right_k = min(a_left, c_right);
            int best_k = 0;
            
            while (left_k <= right_k) {
                int mid_k = (left_k + right_k) / 2;
                
                best_k = mid_k;
                left_k = mid_k + 1;
            }
            
            best_result = max(best_result, 2 * best_k + 1);
        }
        
        cout << best_result << endl;
    }
    
    return 0;
}
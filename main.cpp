#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    
    // Префиксные суммы для 'a', 'b', 'c'
    vector<int> prefa(n + 1, 0), prefb(n + 1, 0), prefc(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefa[i + 1] = prefa[i] + (s[i] == 'a');
        prefb[i + 1] = prefb[i] + (s[i] == 'b');
        prefc[i + 1] = prefc[i] + (s[i] == 'c');
    }
    
    // Вектор позиций 'b'
    vector<int> posb;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'b') posb.push_back(i);
    }
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        
        int cnt_b = prefb[r + 1] - prefb[l];
        if (cnt_b == 0) {
            cout << "0\n";
            continue;
        }
        
        // Находим все 'b' в отрезке [l, r]
        auto it_first = lower_bound(posb.begin(), posb.end(), l);
        auto it_last = upper_bound(posb.begin(), posb.end(), r);
        if (it_first == it_last) {
            cout << "0\n";
            continue;
        }
        
        // Бинарный поиск по оптимальному k для каждой 'b'
        int best_result = 1; // минимум - одна 'b'
        
        for (auto it = it_first; it != it_last; ++it) {
            int b_pos = *it;
            
            // Количество 'a' слева от этой 'b' в отрезке [l, r]
            int a_left = prefa[b_pos + 1] - prefa[l];
            
            // Количество 'c' справа от этой 'b' в отрезке [l, r]
            int c_right = prefc[r + 1] - prefc[b_pos + 1];
            
            // Бинарный поиск по максимальному k
            int left_k = 0;
            int right_k = min(a_left, c_right);
            int best_k = 0;
            
            while (left_k <= right_k) {
                int mid_k = (left_k + right_k) / 2;
                
                // Проверяем, можно ли взять mid_k 'a' слева и mid_k 'c' справа
                // Это всегда возможно, если mid_k <= a_left и mid_k <= c_right
                // (что гарантируется условиями выше)
                
                best_k = mid_k;
                left_k = mid_k + 1;
            }
            
            best_result = max(best_result, 2 * best_k + 1);
        }
        
        cout << best_result << "\n";
    }
    
    return 0;
}
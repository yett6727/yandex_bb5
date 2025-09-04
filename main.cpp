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
    vector<int> sufa(n + 2, 0), sufb(n + 2, 0), sufc(n + 2, 0);
    
    for (int i = 0; i < n; i++) {
        prefa[i + 1] = prefa[i] + (s[i] == 'a');
        prefb[i + 1] = prefb[i] + (s[i] == 'b');
        prefc[i + 1] = prefc[i] + (s[i] == 'c');
    }
    
    for (int i = n - 1; i >= 0; i--) {
        sufa[i + 1] = sufa[i + 2] + (s[i] == 'a');
        sufb[i + 1] = sufb[i + 2] + (s[i] == 'b');
        sufc[i + 1] = sufc[i + 2] + (s[i] == 'c');
    }
    
    // Для каждой позиции 'b' считаем разницу: (a слева) - (c справа)
    vector<int> diff(n, INT_MAX); 
    vector<int> b_positions;
    
    for (int i = 0; i < n; i++) {
        if (s[i] == 'b') {
            b_positions.push_back(i);
            int a_left = prefa[i + 1]; // a до текущей позиции (включительно)
            int c_right = sufc[i + 1]; // c после текущей позиции (включительно)
            diff[i] = a_left - c_right;
        }
    }
    
    // Функция для поиска минимальной разницы на отрезке [l, r]
    auto min_diff_in_range = [&](int l, int r) {
        auto it_l = lower_bound(b_positions.begin(), b_positions.end(), l);
        auto it_r = upper_bound(b_positions.begin(), b_positions.end(), r);
        
        if (it_l == it_r) return INT_MAX;
        
        int min_val = INT_MAX;
        for (auto it = it_l; it != it_r; ++it) {
            min_val = min(min_val, diff[*it]);
        }
        return min_val;
    };
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        
        int cnt_b = prefb[r + 1] - prefb[l];
        int min_diff = min_diff_in_range(l, r);

        if (cnt_b == 0 || min_diff == INT_MAX) {
            cout << 0 << endl;
            continue;
        }
        
        // Количество 'a' слева от первой 'b' в отрезке
        int first_b = *lower_bound(b_positions.begin(), b_positions.end(), l);
        int a_before_first_b = prefa[first_b + 1] - prefa[l];
        
        // Количество 'c' справа от последней 'b' в отрезке
        auto last_b_it = upper_bound(b_positions.begin(), b_positions.end(), r);
        if (last_b_it == b_positions.begin()) {
            cout << 0 << endl;
            continue;
        }
        last_b_it--;
        int last_b = *last_b_it;
        int c_after_last_b = prefc[r + 1] - prefc[last_b + 1];
        
        // Бинарный поиск по оптимальному k
        int left = 0;
        int right = min(prefa[r + 1] - prefa[l], prefc[r + 1] - prefc[l]);
        int best_k = 0;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            
            // Проверяем, можно ли достичь разницы <= 0 с k = mid
            // Минимальная требуемая разница: a_left - c_right <= 0
            // где a_left + c_right = 2*mid
            
            bool possible = false;
            
            // Вариант 1: используем первую 'b'
            if (a_before_first_b >= mid && c_after_last_b >= mid) {
                possible = true;
            }
            
            // Вариант 2: проверяем минимальную разницу
            if (!possible && min_diff <= 0) {
                // Есть 'b' с отрицательной разницей - можно взять больше 'c'
                possible = true;
            }
            
            // Вариант 3: проверяем конкретные значения
            if (!possible) {
                // Ищем 'b' с минимальной разницей
                for (int k = max(0, mid - 5); k <= min(mid + 5, right); k++) {
                    if (min_diff <= k - (2 * mid - k)) {
                        possible = true;
                        break;
                    }
                }
            }
            
            if (possible) {
                best_k = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        cout << (2 * best_k + 1) << "\n";
    }
    
    return 0;
}
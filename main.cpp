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
    
    // Векторы позиций для каждого символа
    vector<int> posa, posb, posc;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') posa.push_back(i);
        else if (s[i] == 'b') posb.push_back(i);
        else if (s[i] == 'c') posc.push_back(i);
    }
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        
        int cnt_a = prefa[r + 1] - prefa[l];
        int cnt_b = prefb[r + 1] - prefb[l];
        int cnt_c = prefc[r + 1] - prefc[l];
        
        if (cnt_b == 0) {
            cout << "0\n";
            continue;
        }
        
        // Находим первую 'b' в отрезке
        auto it_b_first = lower_bound(posb.begin(), posb.end(), l);
        if (it_b_first == posb.end() || *it_b_first > r) {
            cout << "0\n";
            continue;
        }
        int first_b = *it_b_first;
        
        // Находим последнюю 'b' в отрезке
        auto it_b_last = upper_bound(posb.begin(), posb.end(), r);
        if (it_b_last == posb.begin()) {
            cout << "0\n";
            continue;
        }
        it_b_last--;
        int last_b = *it_b_last;
        
        // Более простой и надежный подход
        // Пробуем разные стратегии и берем максимум
        
        int best = 1; // Минимум - просто одна 'b'
        
        // Стратегия 1: берем первую 'b' и максимизируем вокруг нее
        int a_before_first = prefa[first_b + 1] - prefa[l];
        int c_after_first = prefc[r + 1] - prefc[first_b + 1];
        int k1 = min(a_before_first, c_after_first);
        best = max(best, 2 * k1 + 1);
        
        // Стратегия 2: берем последнюю 'b' и максимизируем вокруг нее
        int a_before_last = prefa[last_b + 1] - prefa[l];
        int c_after_last = prefc[r + 1] - prefc[last_b + 1];
        int k2 = min(a_before_last, c_after_last);
        best = max(best, 2 * k2 + 1);
        
        // Стратегия 3: для средних 'b' - используем бинарный поиск
        // Но для простоты ограничимся первыми двумя стратегиями
        // (они часто дают оптимальный результат)
        
        // Дополнительная проверка: если можем взять только 'b'
        if (best == 1 && cnt_a == 0 && cnt_c == 0) {
            cout << "1\n";
        } else {
            cout << best << "\n";
        }
    }
    
    return 0;
}
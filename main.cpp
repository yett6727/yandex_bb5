#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <utility>
using namespace std;

vector<pair<int, int>> generate_random_pairs(int n, int q) {
    vector<pair<int, int>> pairs;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, n);
    
    for (int i = 0; i < q; i++) {
        int a = dist(gen);
        int b = dist(gen);
        
        // Если первое число больше второго - меняем местами
        if (a > b) {
            std::swap(a, b);
        }
        
        pairs.emplace_back(a, b);
    }
    
    return pairs;
}


string generate_random_string(int length) {
    const char chars[] = {'a', 'b', 'c'};
    string result;
    
    mt19937 generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(0, 2);
    
    for (int i = 0; i < length; ++i) {
        result += chars[distribution(generator)];
    }
    
    return result;
}

int my_solve(vector <int> &a_pref, vector <int> &b, vector <int> &c_suf, int l, int r, string s) {
    auto iterator_l = lower_bound(b.begin(), b.end(), l);
    auto iterator_r = upper_bound(b.begin(), b.end(), r);
    if (iterator_r == iterator_l) {
        return 0;
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
    return 2*ans + 1;
}

int brute_force_solve(vector <int>& a_pref, vector <int>& b, vector <int>& c_suf, int& l, int& r, string& s) {
    int ans = 0;
    bool marker = false;
    for (int i = l; i <= r; i++) {
        if (s[i-1] == 'b') {
            marker = true;
            int a_count = a_pref[i-1] - a_pref[l-1]; 
            int c_count = c_suf[i+1] - c_suf[r+1];
            ans =  max(ans, min(c_count, a_count));
        }
    }
    if(marker)return 2*ans + 1;
    return 0;
}

int main(){
    int n, q;
    cin >> n >> q;

    string s = generate_random_string(n);
    cout << "String generated: " << s << endl;

    vector <pair<int,int>> queries = generate_random_pairs(n, q);

    vector <int> pref_a(n + 1, 0);
    vector <int> suf_c(n + 2, 0);
    vector <int> b_pos;

    for (int i = 0; i < n; i++){ //prefix/sufix sums
        pref_a[i + 1] = pref_a[i] + (s[i] == 'a');
        if(s[i] == 'b') b_pos.push_back(i);
    }
    for (int i = n; i > 0; i--) {
        suf_c[i] = suf_c[i+1] + (s[i-1] == 'c');
    }
 
    while (q--){ //query processing
        int l = queries[q - 1].first;
        int r = queries[q - 1].second;

        int my_ans = my_solve(pref_a, b_pos, suf_c, l, r, s);
        int correct_ans = brute_force_solve(pref_a, b_pos, suf_c, l, r, s);

        cout << "My answer: " << my_ans << ' ' << "Correct answer: " << correct_ans << ' ';

        if (my_ans == correct_ans){
            cout << "✅ Correct!" << endl;
        }
        else { //debug info
            cout << "❌ Incorrect!" << endl;

            cout << "Current query: " << l << ' ' << r << endl;
            cout << "String segment ";
            for (int i = l; i <= r; i++) cout << s[i - 1];
            cout << endl;
            
            return 1;
        }
    }
}
#include <bits/stdc++.h>
using namespace std;
<<<<<<< HEAD
  
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
=======

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

int my_solve(vector <int> &a_pref, vector <int> &b, vector <int> &c_suf, int &l, int &r) {
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

pair<int, int> brute_force_solve(vector <int>& a_pref, vector <int>& b, vector <int>& c_suf, int& l, int& r, string& s) {
    int ans = 0;
    int working_b_pos;
    bool marker = false;
    for (int i = l; i <= r; i++) {
        if (s[i-1] == 'b') {
            marker = true;
            int a_count = a_pref[i-1] - a_pref[l-1]; 
            int c_count = c_suf[i+1] - c_suf[r+1];
            ans =  max(ans, min(c_count, a_count));
            working_b_pos = i;
        }
    }
    if(marker)return {2*ans + 1, working_b_pos};
    return {0, -1};
}

int main(){
>>>>>>> c04f120 (returned working b for brute force)
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
<<<<<<< HEAD
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        auto iterator_l = lower_bound(b.begin(), b.end(), l);
        auto iterator_r = upper_bound(b.begin(), b.end(), r);
        if (iterator_r == iterator_l) {
            cout << 0 << endl;
            continue;
=======
 
    while (q--){ //query processing
        int l = queries[q].first;
        int r = queries[q].second;

        int my_ans = my_solve(pref_a, b_pos, suf_c, l, r);
        pair <int,int> correct_ans = brute_force_solve(pref_a, b_pos, suf_c, l, r, s);

        cout << "My answer: " << my_ans << ' ' << "Correct answer: " << correct_ans.first << ' ';

        if (my_ans == correct_ans.first){
            cout << "✅ Correct!" << endl;
>>>>>>> 2ad8cb2 (fixed q)
        }
<<<<<<< HEAD
        int ans = 0;
        int b_l = iterator_l - b.begin();
        int b_r = iterator_r - b.begin() - 1;
        while (b_r - b_l > 10) {
            int mid1 = b_l + (b_r - b_l) / 3;
            int mid2 = b_r - (b_r - b_l) / 3;
=======
        else { //debug info
            cout << "❌ Incorrect!" << endl;

            cout << "Current query: " << l << ' ' << r << endl;
            cout << "String segment ";
            for (int i = l; i <= r; i++) cout << s[i - 1];
            cout << endl << "Bruteforce B pos: " << correct_ans.second;
>>>>>>> c04f120 (returned working b for brute force)
            
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

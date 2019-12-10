//
// Created by inked on 2019/12/10 0010.
//
#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("sample2.in", "r", stdin);
    int n;
    cin >> n;
    vector<int> cnt(n, 0);
    vector<bool> drop(n, false);
    for (int i = 0; i < n; i++) {
        int ni;
        cin >> ni;
        cin >> cnt[i];
        for (int j = 2; j <= ni; j++) {
            int k;
            cin >> k;
            if (k > 0) {
                if (cnt[i] != k) {
                    drop[i] = true;
                    cnt[i] = k;
                }
            } else {
                cnt[i] += k;
            }
        }
    }
    int total = accumulate(cnt.begin(), cnt.end(), 0);
    int cntDrop = count(drop.begin(), drop.end(), true);
    int cntDropGroup = 0;
    for (int i = 0; i < n; i++) {
        int pred = (i - 1) % n, succeed = (i + 1) % n;
        if (pred < 0) pred += n;
        if (succeed < 0) succeed += n;
        if (drop[i] && drop[pred] && drop[succeed])
            cntDropGroup++;
    }
    cout << total << " " << cntDrop << " " << cntDropGroup << endl;
}
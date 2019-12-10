//
// Created by inked on 2019/12/10 0010.
//
#include <bits/stdc++.h>
using namespace std;

#ifdef _DEBUG
#include "../util/redirect.h"
#endif

int main() {
#ifdef _DEBUG
    redirect_input("sample2.in");
#endif
    clog.setstate(clog.failbit);
    int n, m;
    cin >> n >> m;
    int total = 0;
    vector<int> change(n, 0);
    for (int i = 1; i <= n; i++) {
        int cnt;
        cin >> cnt;
        total += cnt;
        clog << "add" << cnt << endl;
        for (int j = 1; j <= m; j++) {
            int delta;
            cin >> delta;
            total += delta;
            clog << "minus " << delta << endl;
            change[i - 1] += delta;
        }
    }
    int minPos = 0, min = change[minPos];
    for (int i = 1; i < n; i++) {
        if (min > change[i]) {
            minPos = i;
            min = change[i];
        }
    }
    cout << total << " ";
    cout << minPos+1 << " " << -min <<endl;
}
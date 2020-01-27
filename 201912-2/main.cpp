#include <bits/stdc++.h>
using namespace std;

set<pair<int, int>> p;
vector<int> cnt(5);
set<pair<int, int>> pre;

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    int minx = 100000, miny = 100000;
    int maxx = -1, maxy = -1;
    while (n--) {
        int xi, yi;
        cin >> xi >> yi;
        p.emplace(xi, yi);
        pre.emplace(xi, yi);
        pre.emplace(xi-1, yi);
        pre.emplace(xi+1, yi);
        pre.emplace(xi, yi-1);
        pre.emplace(xi, yi+1);
        if (xi < minx) {
            minx = xi;
        }
        if (xi > maxx) {
            maxx = xi;
        }
        if (yi < miny) {
            miny = yi;
        }
        if (yi > maxy) {
            maxy = yi;
        }
    }
    for (auto xp : pre) {
        int &xx = xp.first;
        int &yy = xp.second;
            if (p.count({xx, yy})
                && p.count({xx, yy - 1})
                && p.count({xx, yy + 1})
                && p.count({xx - 1, yy})
                && p.count({xx + 1, yy})
                    ) {
                int score = 0;
                if (p.count({xx - 1, yy - 1})) {
                    ++score;
                }
                if (p.count({xx - 1, yy + 1})) {
                    ++score;
                }
                if (p.count({xx + 1, yy - 1})) {
                    ++score;
                }
                if (p.count({xx + 1, yy + 1})) {
                    ++score;
                }
                ++cnt[score];
            }
    }
    cout << cnt[0] << endl
         << cnt[1] << endl
         << cnt[2] << endl
         << cnt[3] << endl
         << cnt[4] << endl;
}

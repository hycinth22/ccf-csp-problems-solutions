#include <bits/stdc++.h>

using namespace std;

#ifndef _DEBUG
struct fakeOSType {
    template<class contentType>
    inline fakeOSType &operator<<(const contentType &cont) {return *this;}
    inline fakeOSType &operator<<(ostream &op(ostream &)) {return *this;}
} nullos;
#define clog nullos
#define cerr nullos
#endif

int times[4] = {0, 0, 0, 0};

bool skip(int x) {
    if (x % 7 == 0) return true;
    while (x > 0) {
        if (x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}

int main() {
    assert(!skip(6)); assert(!skip(1));
    assert(skip(7));  assert(skip(17));  assert(skip(71)); assert(skip(711)); assert(skip(117)); assert(skip(171));
    ios_base::sync_with_stdio(false);
    // n: 要喊的数的数量
    // i: 要喊的数
    // cnt：已喊的数
    int n, i=1;
    cin >> n;
    for(int cnt=0; cnt<n; i++) {
        int who = (i-1)%4;
        if(skip(i)) {
            clog << who << " skip " << i << endl;
            times[who]++;
        } else {
            clog << who << " say " << i << endl;
            cnt++;
        }
    }
    cout << times[0] << endl
    << times[1] << endl
    <<  times[2] << endl
    <<  times[3] << endl;
}

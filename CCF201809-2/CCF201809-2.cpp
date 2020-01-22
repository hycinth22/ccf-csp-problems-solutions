/*
问题描述
小H和小W来到了一条街上，两人分开买菜，他们买菜的过程可以描述为，去店里买一些菜然后去旁边的一个广场把菜装上车，两人都要买n种菜，所以也都要装n次车。具体的，对于小H来说有n个不相交的时间段[a1, b1], [a2, b2]...[an, bn]在装车，对于小W来说有n个不相交的时间段[c1, d1], [c2, d2]...[cn, dn]在装车。其中，一个时间段[s, t]表示的是从时刻s到时刻t这段时间，时长为t - s。
由于他们是好朋友，他们都在广场上装车的时候会聊天，他们想知道他们可以聊多长时间。
输入格式
输入的第一行包含一个正整数n，表示时间段的数量。
接下来n行每行两个数ai，bi，描述小H的各个装车的时间段。
接下来n行每行两个数ci，di，描述小W的各个装车的时间段。
输出格式
输出一行，一个正整数，表示两人可以聊多长时间。
样例输入
4
1 3
5 6
9 13
14 15
2 4
5 7
10 11
13 14
样例输出
3
数据规模和约定
对于所有的评测用例，1 ≤ n ≤ 2000, ai < bi < ai + 1，ci < di < ci + 1, 对于所有的i(1 ≤ i ≤ n)有，1 ≤ ai, bi, ci, di ≤ 1000000。
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct td{
	int be;
	int end;
};

int jtd(const td& t1, const td& t2) {
	int b = max(t1.be, t2.be);
	int e = min(t1.end, t2.end);
	int d = e - b;
	if (d < 0) {
		return 0;
	}
	return d;
}

int main()
{
	int n; cin >> n;
	vector<td> t1(n), t2(n);
	for (auto& d : t1) {
		cin >> d.be >> d.end;
	}
	for (auto& d : t2) {
		cin >> d.be >> d.end;
	}
	int ans = 0;
	for (auto& d1 : t1) {
		for (auto& d2 : t2) {
			auto add = jtd(d1, d2);
			ans += add;
		}
	}
	cout << ans << endl;
	return 0;
}
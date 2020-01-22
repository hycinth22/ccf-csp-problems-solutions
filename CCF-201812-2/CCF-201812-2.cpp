/*

题目背景
　　汉东省政法大学附属中学所在的光明区最近实施了名为“智慧光明”的智慧城市项目。具体到交通领域，通过“智慧光明”终端，可以看到光明区所有红绿灯此时此刻的状态。小明的学校也安装了“智慧光明”终端，小明想利用这个终端给出的信息，估算自己放学回到家的时间。
问题描述
　　一次放学的时候，小明已经规划好了自己回家的路线，并且能够预测经过各个路段的时间。同时，小明通过学校里安装的“智慧光明”终端，看到了出发时刻路上经过的所有红绿灯的指示状态。请帮忙计算小明此次回家所需要的时间。
输入格式
　　输入的第一行包含空格分隔的三个正整数 r、y、g，表示红绿灯的设置。这三个数均不超过 10^6。
　　输入的第二行包含一个正整数 n，表示小明总共经过的道路段数和路过的红绿灯数目。
　　接下来的 n 行，每行包含空格分隔的两个整数 k、t。k=0 表示经过了一段道路，将会耗时 t 秒，此处 t 不超过 10^6；k=1、2、3 时，分别表示出发时刻，此处的红绿灯状态是红灯、黄灯、绿灯，且倒计时显示牌上显示的数字是 t，此处 t 分别不会超过 r、y、g。
输出格式
　　输出一个数字，表示此次小明放学回家所用的时间。
样例输入
30 3 30
8
0 10
1 5
0 11
2 2
0 6
0 3
3 10
0 3
样例输出
46
样例说明
　　小明先经过第一段路，用时 10 秒。第一盏红绿灯出发时是红灯，还剩 5 秒；小明到达路口时，这个红绿灯已经变为绿灯，不用等待直接通过。接下来经过第二段路，用时 11 秒。第二盏红绿灯出发时是黄灯，还剩两秒；小明到达路口时，这个红绿灯已经变为红灯，还剩 11 秒。接下来经过第三、第四段路，用时 9 秒。第三盏红绿灯出发时是绿灯，还剩 10 秒；小明到达路口时，这个红绿灯已经变为红灯，还剩两秒。接下来经过最后一段路，用时 3 秒。共计 10+11+11+9+2+3 = 46 秒。
评测用例规模与约定
　　有些测试点具有特殊的性质：
　　* 前 2 个测试点中不存在任何信号灯。
　　测试点的输入数据规模：
　　* 前 6 个测试点保证 n ≤ 10^3。
　　* 所有测试点保证 n ≤ 10^5。
*/

#include "pch.h"
#include <iostream>
#include <cstdio>
using namespace std;

using timeDuration = unsigned long long;

int stageTime[3];
// ->1->3->2->
void nextState(int &k) {
	switch (k) {
	case 1: // red
		k = 3;
		break;
	case 2: // yellow
		k = 1;
		break;
	case 3: // green
		k = 2;
		break;
	}
}

void preState(int &k) {
	switch (k) {
	case 1: // red
		k = 2;
		break;
	case 2: // yellow
		k = 3;
		break;
	case 3: // green
		k = 1;
		break;
	}
}

inline int getStageTime(const int& k) {
	return stageTime[k-1];
}

void calcState(timeDuration time, int& k, timeDuration& t) {
	const timeDuration cycle = stageTime[0] + stageTime[1] + stageTime[2];
	time %= cycle;
	if (time < t) {
		t -= time;
		return;
	}
	time -= t; nextState(k); // frist part stage
	bool proceed = true;
	timeDuration stageTime;
	while (time > 0) {
		stageTime = getStageTime(k);
		if (time < stageTime) {
			t = stageTime - time; // final part stage
			break;
		}
		time -= stageTime;  nextState(k); // proceed entire stage
	}
	return;
}

int main()
{
	int &r = stageTime[0], &y = stageTime[1], &g= stageTime[2];
	cin >> r >> y >> g;
	timeDuration n; cin >> n;
	timeDuration ans = 0;
	for (timeDuration i = 0; i < n; i++) {
		// clog << "当前时间点：" << ans << endl;
		int k; timeDuration t; cin >> k >> t;
		if (k == 0) {
			ans += t;
			continue;
		}
		// clog << "初始状态：" << k << " " << t << endl;
		calcState(ans, k, t);
		// clog << "达到状态：" << k << " " << t << endl;
		switch (k)
		{
		case 1: // R
			ans += t;
			break;
		case 2: // Y
			ans += t + r;
			break;
		case 3: // G
			ans += 0;
			break;
		default:
			break;
		}
	}
	cout << ans << endl;
	return 0;
}

/*
解题要点：

模拟题，比前一题稍微复杂，可在前一题基础上修改。

1. 经过一个完整的红绿黄周期，状态相当于没有任何变化。
因此通过对整个周期取余，可以大大节省运算时间。
而后只要进行小于两个周期的模拟，即可得出结果。

2. 注意模拟循环中：
->红->绿->黄->
对应的数字是
->1->3->2->
不要想当然认为是->1->2->3->，从而写错代码。

3. 分析数据规模，可知：
- r、y、g最大为10^6，n最大为10^5，使用int存储没有任何问题。
- 但结果ans考虑最大的情况（全部遇到为黄灯刚开始）下，为ans=n*(y+r)，10^5*(10^6+10^6)=2*10^11次方，
不可以直接使用int、unsigned int，都达不到要求（可以使用<limits>的numeric_limits<T>::min()/max()查询类型T的表示范围）。
需要使用long long或者unsigned long long替换相关类型。
如果没有注意数据规模问题，将导致最后两个测试点不通过。

*/
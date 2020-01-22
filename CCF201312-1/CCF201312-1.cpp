// CCF_Problems.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

/*
问题描述
给定n个正整数，找出它们中出现次数最多的数。如果这样的数有多个，请输出其中最小的一个。
输入格式
输入的第一行只有一个正整数n(1 ≤ n ≤ 1000)，表示数字的个数。
输入的第二行有n个整数s1, s2, …, sn (1 ≤ si ≤ 10000, 1 ≤ i ≤ n)。相邻的数用空格分隔。
输出格式
输出这n个次数中出现次数最多的数。如果这样的数有多个，输出其中最小的一个。
样例输入
6
10 1 10 20 30 20
样例输出
10
*/

#include "pch.h"
#include <iostream>
#include <map>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::map;

int main()
{
	int n; cin >> n;
	map<int, int> m;
	for (int i = 0; i < n; i++) {
		int key; cin >> key;
		m[key]++;
	}
	std::pair<int, int> ans = *m.cbegin();
	for (auto pair: m) {
		// 找到次数最多的一个。
		// map保证key更小的在前面，于是我们遍历时忽略相等便可以得到最小的元素。
		if (pair.second > ans.second) {
			ans = pair;
		}
	}
	cout << ans.first;
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

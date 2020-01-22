/*
题目描述见图片p3_1.png、p3_2.png、p3_3.png

样例输入
2
1
2
样例输出
1.0.0.0/8
2.0.0.0/8

样例输入
2
10/9
10.128/9
样例输出
10.0.0.0/8

样例输入
2
0/1
128/1
样例输出
0.0.0.0/0

数据规模见图片p3_4.png、p3_5.png

*/
#include "pch.h"
#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

using IPAddr = unsigned int;
using Byte = unsigned char;
struct IPPrefix {
	Byte ip[4];
	short len;
	bool isSubsetOf(const IPPrefix& o) {
		if (this->len < o.len) {
			return false;
		}
		auto lessLen = o.len;
		IPAddr mask = 0;
		for (int i = 0; i < lessLen; i++) {
			mask |= 1U << (32 - (i+1));
		}
		IPAddr ip1 = this->getIP();
		IPAddr ip2 = o.getIP();
		IPAddr ip1subnet = ip1 & mask;
		IPAddr ip2subnet = ip2 & mask;
		return ip1subnet == ip2subnet;
	}
	inline IPAddr getIP() const {
		return ip[0] << 24
			| ip[1] << 16
			| ip[2] << 8
			| ip[3];
	}
	bool operator==(IPPrefix& rhs) const {
		return this->getIP() == rhs.getIP() 
			&& this->len == rhs.len;
	}
};


int stoi(const string& str) {
	int r;
	stringstream ss;
	ss << str;
	ss >> r;
	return r;
}

inline istream& operator>>(istream& is, IPPrefix& rhs) {
	string input; cin >> input;
	string::size_type si = input.find_first_of('/');
	string ipStr = input.substr(0, si);
	string::size_type preDot = -1;
	string::size_type nextDot = ipStr.find_first_of('.');
	rhs.ip[0] = stoi(ipStr.substr(0, nextDot));
	preDot = nextDot;
	int sectionCnt = 1;
	for (int i = 1; i < 4; i++) {
		if (preDot == string::npos) {
			rhs.ip[i] = 0;
		}
		else {
			nextDot = ipStr.find_first_of('.', preDot + 1);
			sectionCnt++;
			string ipSection = ipStr.substr(preDot + 1, nextDot - (preDot + 1));
			rhs.ip[i] = stoi(ipSection);
			preDot = nextDot;
		}
	}

	if (si == string::npos) {
		rhs.len = 8 * sectionCnt;
	}
	else {
		rhs.len = stoi(input.substr(si + 1));
	}
	return is;
}

inline ostream& operator<<(ostream& os, const IPPrefix& rhs) {
	printf("%d.%d.%d.%d/%d", rhs.ip[0], rhs.ip[1], rhs.ip[2], rhs.ip[3], rhs.len);
	return os;
}

inline void optimizeList(list<IPPrefix>& data) {
	data.sort([](const IPPrefix& lhs, const IPPrefix& rhs) {
		IPAddr ip1 = lhs.getIP();
		IPAddr ip2 = rhs.getIP();
		return ip1 < ip2 
			||
			(ip1 == ip2 && lhs.len < rhs.len);
	});
	// 消除子集
	for (auto i1 = data.begin(), i2 = ++data.begin(); i2 != data.end(); i1++, i2++) {
		//clog << "compare1 " << *i1 << " & " << *i2 << endl;
		while (i2!=data.end() && i2->isSubsetOf(*i1)) {
			// clog << *i2 << " is subset of " << *i1 << ", erase former"<< endl;
			i2 = data.erase(i2);
		}
		if (i2 == data.end()) {
			break;
		}
		//clog << "compare1 " << *i1 << " & " << *i2 << endl;
	}
	// 合并同级
	auto i1 = data.begin(), i2 = ++data.begin();
	while (i2 != data.end()) {
		if (i1->len == i2->len) {
			IPAddr ip1 = i1->getIP();
			IPAddr ip2 = i2->getIP();
			auto len = i1->len;
			// clog << "compare2 " << *i1 << " & " << *i2 << endl;
			if ((ip1 ^ ip2) >> (32 - len) == 1U)  // 前len-1位相同且第len位不同 
			{
				// 合并
				// clog << "merge " << *i1 << " &" << *i2 << endl;
				i1->len--;
				i2 = data.erase(i2);
				// clog << "into " << *i1 << endl;
				// 回退
				if (i1 != data.begin()) {
					i1--;
					i2--;
					continue;
				}
				if (i2 == data.end()) {
					break;
				}
			}
		}
		// 前进
		i1++; i2++;
	}
}

int main()
{
	size_t n; cin >> n;
	list<IPPrefix> list(n);
	for (auto it = list.begin(); it != list.end(); it++) {
		cin >> *it;
	}
	optimizeList(list);
	for (auto it = list.cbegin(); it != list.cend(); it++) {
		cout << *it << endl;
	}
}

/*
解题要点：

1. 定义存储IP前缀的结构体，并在输入时完成标准化,有助于简化后续处理. 输出时则只需要输出标准格式.

2. 排序时，由于STL list不是随机访问容器，不能使用`<algorithm>`库的`sort(RandomIterator begin, RandomIterator end, Compare pred)`，
但STL list容器自身提供了排序方法`list.sort(Compare pred)`

同时，由于是自定义结构，需要自行编写STL Compare，可以使用lambda表达式，也可以使用普通函数。
注意如何编写合法的STL Compare（需满足严格弱序、返回值代表第一个参数是否比第二个参数先出现）。

3. 位运算相关知识。
还可能涉及整型提升（Integer Promotion）。

4. 对题目提示阅读理解及实现
第二步从小到大合并，即为消除被其他前缀包含的子集前缀过程的过程。
只要按较短的一个前缀的长度len，比较两个IP前缀的前len位是否相同，相同则代表长度较长的那个是长度较短的子集。
由于排序保证后者范围更小，因此后者是子集，保留前者，删去后者。
（此过程中也可以两前缀的长度相同，如果前len位相同，则代表两个前缀等价。
由于排序保证后者地址更大，因此后者地址段包含无效数据更多，也是保留前者，删去后者）

第三步同级合并，即为将两个相同长度的前缀，合并为一个更短的前缀。
只要判断两个前缀的最后一个有效位不同，且前面len-1位相同，则可以两者合并为一个len-1长度的前缀。
可以用异或运算。

以上两步都要注意，由于在循环遍历中修改了遍历对象，无论对迭代器做前进还是后退更改，都要再次考虑迭代器的有效性、是否破坏了循环过程。

5. 由于简化过程中需要大量修改容器内容，不要使用顺序容器vector等储存，
否则修改时造成大量元素复制时间，后几个大规模测试数据中极易超时。
推荐使用STL的list存储。

输入时，也可以预先申请空间而不是每次输入都调用push。

*/

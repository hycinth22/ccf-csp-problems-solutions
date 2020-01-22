/*

样例输入
4
5
1
1 2 3
1 3 4
1 4 5
2 3 8
3 4 2
样例输出
4
样例说明
　　下图是样例说明。

*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
public:
	using size_type = size_t;
	Graph(size_type n)
		: rel (n, vector<bool>(n, false) ) {
		nodes = new GraphNode[n];
	}
	~Graph() {
		delete[] nodes;
	}
	void AddBidirectLine(size_type begin, size_type end) {
		rel[begin][end] = true;
		rel[end][begin] = true;
	}
	queue<GraphNode> getRelated(size_type id) {
		queue<GraphNode> q;
		vector<bool>::size_type size = rel[id].size();
		for (vector<bool>::size_type i = 0; i < size; i++) {
			if (rel[id][i]) {
				q.push(nodes[i]);
			}
		}
		return q;
	}
private:
	GraphNode* nodes;
	vector<vector<bool>> rel;
};

struct GraphNode {
	int id;
};

int main()
{
    std::cout << "Hello World!\n"; 
}
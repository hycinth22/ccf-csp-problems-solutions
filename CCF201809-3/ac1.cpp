// CCF201809-3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
/*
11 5
html
..head
....title
..body
....h1
....p #subtitle
....div #main
......h2
......p #one
......div
........p #two
p
#subtitle
h3
div p
div div p
*/
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iterator>
#include <cctype>
using namespace std;

struct Element {
	string tagname;
	string id;
	int depth;
	int line;
	Element* parent;
	vector<Element*> childs;
};
struct Selector {
	virtual bool match(Element* elem) = 0;
};
struct TagSelector:Selector {
	string tagname;
	bool match(Element* elem) {
		return tagname == elem->tagname;
	}
};
struct IDSelector:Selector {
	string id;
	bool match(Element* elem) {
		return id == elem->id;
	}
};
struct TwoGrandChildSelector :Selector {
	Selector* firstSel;
	Selector* secondSel;
	bool match(Element* elem) {
		if (!secondSel->match(elem)) {
			return false;
		}
		Element* e = elem->parent;
		while (e != nullptr) {
			if (firstSel->match(e)) {
				return true;
			}
			e = e->parent;
		}
		return false;
	}
};
struct GrandChildSelector :Selector {
	vector<Selector*> Sels;
	bool match(Element* elem) {
		if (Sels.empty()) { return false; }
		reverse_iterator<vector<Selector*>::const_iterator> it = Sels.crbegin();
		if (!(*it)->match(elem)) {
			return false;
		}
		it++;
		while (it != Sels.crend()) {
			Element* e = elem->parent;
			while (e != nullptr) {
				if ((*it)->match(e)) {
					elem = e;
					break; // 匹配下一个Selector
				}
				e = e->parent;
			}
			if (e == nullptr) {
				return false; // 此Selector匹配失败
			}
			it++;
		}
		return true;
	}
};
Selector* createSelector(string sel) {
	if (sel.size() <= 0) {
		return new TagSelector();
	}
	vector<string> g;
	string::size_type last = 0;
	string::size_type space = sel.find(' ');
	while (space != string::npos) {
		g.push_back(sel.substr(last, space-last));
		last = space + 1;
		space = sel.find(' ', last);
	}
	g.push_back(sel.substr(last));
	if (g.size() == 2) {
		auto s = new TwoGrandChildSelector();
		s->firstSel = createSelector(g[0]);
		s->secondSel = createSelector(g[1]);
		return s;
	}
	else if (g.size() > 2) {
		auto s = new GrandChildSelector();
		for (auto & subSel : g) {
			s->Sels.push_back(createSelector(subSel));
		}
		return s;
	}
	else if (sel[0] == '#') {
		auto s = new IDSelector();
		s->id = sel.substr(1);
		return s;
	}
	else {
		auto s = new TagSelector();
		s->tagname = sel;
		for_each(s->tagname.begin(), s->tagname.end(), ::toupper);
		return s;
	}
}
struct SelectResult{
	SelectResult() :
		Count(0), Lines()
	{}
	int Count;
	vector<int> Lines;
};

SelectResult select(Selector* sel, Element* root) {
	SelectResult result;
	if (sel->match(root)) {
		result.Count = 1;
		result.Lines.push_back(root->line);
	}
	for (auto c:root->childs) {
		SelectResult subResult = select(sel, c);
		result.Count += subResult.Count;
		result.Lines.insert(result.Lines.end(), subResult.Lines.cbegin(), subResult.Lines.cend());
	}
	sort(result.Lines.begin(), result.Lines.end());
	return result;
}

// TODO: How to free
Element* parseElementFromS(string s) {
	auto elem = new Element();
	auto contentI = s.find_first_not_of('.');
	auto contentEnd = s.find_first_of(' ', contentI);
	auto other = s.find_first_of('#', contentEnd);
	if (other == string::npos) {
		elem->tagname = s.substr(contentI);
		elem->id = "";
	}
	else {
		elem->tagname = s.substr(contentI, contentEnd-contentI);
		elem->id = s.substr(other+1);
	}
	for_each(elem->tagname.cbegin(), elem->tagname.cend(), ::toupper);
	elem->depth = contentI / 2;
	return elem;
}

int main()
{
	int n, m; cin >> n >> m; cin.get();
	Element* root = nullptr;
	stack<Element*> chain; // stackDepth = stack.size()-1
	for (int i = 0; i < n; i++) {
		string s; getline(cin, s);
		Element* elem = parseElementFromS(s);
		elem->line = i+1;
		if (chain.empty()) {
			root = elem;
			elem->parent = nullptr;
			chain.push(elem);
		}
		else {
			int chainDepth = chain.size() - 1;
			if (elem->depth > chainDepth + 1) {
				return -1;
			}
			while (elem->depth <= chainDepth) {
				chain.pop();
				chainDepth--;
			}
			elem->parent = chain.top();
			chain.top()->childs.push_back(elem);
			chain.push(elem);
		}
	}
	for (int i = 0; i < m; i++) {
		string sel; getline(cin, sel);
		auto selector = createSelector(sel);
		auto s = select(selector, root);
		cout << s.Count;
		for (auto l : s.Lines) {
			cout << " " << l ;
		}
		cout << endl;
	}
	return 0;
}
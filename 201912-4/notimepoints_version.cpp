//
// Created by inked on 2020/3/7 0007.
//

#include <bits/stdc++.h>
using namespace std;

using nodeid_t = int;
using chain_t = vector<nodeid_t>;
using broadcastMsg = pair<nodeid_t, chain_t>; // 发出节点ID，主链
vector<vector<nodeid_t> > rel; // 节点-邻接表{相连节点...}
vector<chain_t> chain;// 节点-主链{主链节点...}
map<int, vector<pair<nodeid_t, int>>> creation; // 时间- {{节点，块编号}...}
map<int, vector<broadcastMsg> > transmission; // 时间- {节点，链{接收链组成节点...｝}...}
int n;
int delay;

inline void broadcastNeighbor(int node, int tp) { transmission[tp + delay].push_back({node, chain[node]}); }

// 处理接收
inline void processTransmit(int tp, const vector<broadcastMsg> &allMsg) {
    for (const auto &msg: allMsg) {
        const auto &fromid = msg.first;
        const auto &sentchain = msg.second;
        for (const auto &toid: rel[fromid]) {
            if (chain[toid].size() < sentchain.size()
                || (chain[toid].size() == sentchain.size() && chain[toid].back() > sentchain.back())
                    ) {
                chain[toid] = sentchain; // 接受更新
                broadcastNeighbor(toid, tp); // 向邻居广播自己的主链
            }
        }
    }
}

// 处理创建
inline void processCreate(int tp, const vector<pair<nodeid_t, int>> &allCreation) {
    for (const auto &p: allCreation) {
        const auto &nodeid = p.first;
        const auto &blockid = p.second;
        chain[nodeid].push_back(blockid); // 主链延长
        broadcastNeighbor(nodeid, tp); // 向邻居广播自己的主链
    }
}

void processAndQuery(int node, int t) {
    // 注意相同时间点上创建和传输都存在，优先处理接收
    auto itc = creation.cbegin();
    auto itt = transmission.cbegin();
    recheck:
    while (itt != transmission.cend() && itc != creation.cend()
           && min(itc->first, itt->first) <= t) {
        if (itt->first <= itc->first) {
            processTransmit(itt->first, itt->second);// 处理接收
            transmission.erase(itt++);
        } else {
            processCreate(itc->first, itc->second);  // 处理创建
            creation.erase(itc++);
        }
    }
    while (itt != transmission.cend() && itt->first <= t) {
        processTransmit(itt->first, itt->second);// 处理接收
        transmission.erase(itt++);
    }
    if (itc != creation.cend() && itc->first <= t) {
        processCreate(itc->first, itc->second);// 处理创建
        creation.erase(itc++);
        itt = transmission.cbegin();
        goto recheck;
    }
    // 输出该时间点状态
    cout << chain[node].size();
    for (int b: chain[node]) {
        cout << " " << b;
    }
    cout << endl;
}

inline void gen(int node, int t, int id) { creation[t].push_back({node, id}); }

int main() {
    ios_base::sync_with_stdio(false);
    int m;
    cin >> n >> m;
    rel.resize(n + 1);
    chain.resize(n + 1, chain_t(1, 0));
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        rel[u].push_back(v);
        rel[v].push_back(u);
    }
    int k;
    cin >> delay >> k;
    for (int i = 1; i <= k; ++i) {
        int a, b, c;
        cin >> a >> b;
        if (cin.get() == '\n' || cin.eof()) {
            processAndQuery(a, b);
        } else {
            cin >> c;
            gen(a, b, c);
        }
    }
}
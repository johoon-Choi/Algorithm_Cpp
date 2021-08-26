#include <iostream>
#include <vector>
#include <queue>
#define cost first
#define vertex second

using namespace std;
typedef pair<int, int> PII;

const int INF = 2'100'000'000;
int V, E;
int K;
vector<vector<PII>> node;

void solve(int K) {
	vector<int> cost_to(V + 1, INF); // cost[i] == (K) ---> (i) 's min cost
	priority_queue<PII, vector<PII>, greater<PII>> pq;

	cost_to[K] = 0;
	pq.push(PII(cost_to[K], K));

	while (!pq.empty()) {
		int curCost = pq.top().cost;
		int curVer = pq.top().vertex;

		pq.pop();

		if (curCost > cost_to[curVer]) continue;

		for (int i = 0; i < node[curVer].size(); i++) {
			int nextVer = node[curVer][i].vertex;
			int nextCost = curCost + node[curVer][i].cost;

			if (cost_to[nextVer] > nextCost) {
				cost_to[nextVer] = nextCost;
				pq.push(PII(nextCost, nextVer));
			}
		}
	}

	for (int i = 1; i < cost_to.size(); i++) {
		if (cost_to[i] != INF) cout << cost_to[i] << '\n';
		else cout << "INF" << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> V >> E;
	cin >> K;

	node.resize(V + 1);

	for (int i = 0; i < E; i++) {
		int s, e, v;
		cin >> s >> e >> v;

		node[s].push_back(PII(v, e));
	}

	solve(K);
}
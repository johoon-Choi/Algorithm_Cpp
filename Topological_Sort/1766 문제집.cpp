#include <iostream>
#include <vector>
#include <queue>
#define ind first
#define node second

using namespace std;
typedef pair<int, int> pii;

int n, k;

struct comp {
	bool operator ()(pii a, pii b) {
		return a.ind > b.ind;
	}
};

priority_queue<int, vector<int>, greater<int>> pq;
vector<bool> visit;
vector<int> inDegree;
vector<vector<int>> outDegree;


void init() {
	cin >> n >> k;

	inDegree.assign(n + 1, 0);
	outDegree.resize(n + 1);
	visit.assign(n + 1, false);

	int a, b;
	for (int i = 0; i < k; i++) {
		cin >> a >> b;

		inDegree[b]++;
		outDegree[a].push_back(b);
	}
}

void setPQ() {
	for (int i = 1; i <= n; i++)
		if (inDegree[i] == 0) pq.push(i);
}

void solve() {
	int cur;

	while (!pq.empty()) {
		cur = pq.top();
		pq.pop();
		visit[cur] = true;

		cout << cur << ' ';

		for (auto& e : outDegree[cur])
			if (--inDegree[e] == 0) pq.push(e);
	}
}

int main() {
	init();
	setPQ();
	solve();
}
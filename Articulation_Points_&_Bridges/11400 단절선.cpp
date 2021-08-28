#include <iostream>
#include <vector>
#include <queue>
#define MAX 100000

using namespace std;
typedef pair<int, int> pii;

struct comp {
	bool operator()(pii a, pii b) {
		if (a.first != b.first) return a.first > b.first;
		else return a.second > b.second;
	}
};

priority_queue<pii, vector<pii>, comp> pq;
vector<int> adj[MAX + 1];
int visitCount[MAX + 1];
bool dan[MAX + 1];
int v, e;
int cnt = 1;

int dfs(int curVer, int parVer) {
	visitCount[curVer] = cnt++;

	int minVisit = visitCount[curVer];
	int low = MAX;

	for (auto curChild : adj[curVer]) {
		if (curChild == parVer) continue;

		if (visitCount[curChild] == 0) {
			low = dfs(curChild, curVer);

			if (low > visitCount[curVer])
				pq.push({ min(curVer, curChild), max(curVer, curChild) });

			minVisit = min(minVisit, low);

		}
		else minVisit = min(minVisit, visitCount[curChild]);
	}
	return minVisit;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> v >> e;

	int a, b;
	for (int i = 0; i < e; i++) {
		cin >> a >> b;

		adj[a].push_back(b);
		adj[b].push_back(a);
	}


	dfs(1, 0);
	cout << pq.size() << '\n';
	while (!pq.empty()) {
		cout << pq.top().first << ' ' << pq.top().second << '\n';
		pq.pop();
	}
}
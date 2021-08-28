#include <iostream>
#include <vector>
#include <queue>
#define MAX 100000

using namespace std;

priority_queue<int, vector<int>, greater<int>> ans;
vector<vector<int>> adj;
vector<int> visitCount;
vector<bool> ansCount;
int v, e;
int cnt = 1;

int dfs(int curVer, bool isRoot, int parent) {
	visitCount[curVer] = cnt++;

	int minVisit = visitCount[curVer];
	int childCount = 0;
	int low = MAX;

	for (auto curChild : adj[curVer]) {
		if (curChild == parent) continue;

		if (visitCount[curChild] == 0) {
			childCount++;

			low = dfs(curChild, false, curVer);

			if (!isRoot && low >= visitCount[curVer]) {
				if (!ansCount[curVer]) {
					ans.push(curVer);
					ansCount[curVer] = true;
				}
			}

			minVisit = min(minVisit, low);
		}
		else minVisit = min(minVisit, visitCount[curChild]);
	}

	if (isRoot && 2 <= childCount) {
		if (!ansCount[curVer]) {
			ans.push(curVer);
			ansCount[curVer] = true;
		}
	}

	return minVisit;
}

int main() {
	iostream::sync_with_stdio(0);
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> v >> e;
	adj.resize(v + 1);
	ansCount.assign(v + 1, false);
	visitCount.assign(v + 1, 0);

	for (int i = 1; i <= e; i++) {
		int a, b; cin >> a >> b;

		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (int i = 1; i <= v; i++) {
		if (visitCount[i] == 0)
			dfs(i, true, 0);
	}

	cout << ans.size() << '\n';

	while (!ans.empty()) {
		cout << ans.top() << ' ';
		ans.pop();
	}
}
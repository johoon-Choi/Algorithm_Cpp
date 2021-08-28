#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[20001];
int visit[20001];

int tc;
int v, e;
bool answer = true;

void dfs(int curVer, int color) {
	visit[curVer] = color;

	for (auto nextVer : adj[curVer]) {
		if (visit[nextVer] && (visit[nextVer] & 1) == (color & 1)) ::answer = false;
		if (!::answer) return;

		if (visit[nextVer] == 0) dfs(nextVer, color + 1);
	}
}

void init() {
	for (int i = 0; i <= v; i++) {
		adj[i].clear();
		visit[i] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> tc;

	while (tc--) {
		cin >> v >> e;

		init();

		int a, b;
		for (int i = 0; i < e; i++) {
			cin >> a >> b;

			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		for (int i = 1; i <= v && ::answer; i++)
			if (visit[i] == 0) dfs(i, 1);

		if (::answer) cout << "YES" << '\n';
		else cout << "NO" << '\n';

		::answer = true;
	}
}
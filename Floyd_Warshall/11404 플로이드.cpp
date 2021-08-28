#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long ull;

const ull INF = ull(1e15);
vector<vector<ull>> floyd;
int V, E;

void Floyd_Warshall() {
	for (int visit = 1; visit <= V; visit++) {
		for (int i = 1; i <= V; i++) {
			for (int j = 1; j <= V; j++) {
				if (i != visit && j != visit) {
					floyd[i][j] = min(floyd[i][j], floyd[i][visit] + floyd[visit][j]);
				}
			}
		}
	}

	for (int i = 1; i <= V; i++) {
		for (int j = 1; j <= V; j++)
			cout << (floyd[i][j] != INF ? floyd[i][j] : 0) << ' ';
		cout << '\n';
	}
}

int main() {
	cin >> V >> E;
	floyd.assign(V + 1, vector<ull>(V + 1, INF));

	for (int i = 1; i <= V; i++) floyd[i][i] = 0;

	for (int i = 0; i < E; i++) {
		ull s, e, cst;
		cin >> s >> e >> cst;

		floyd[s][e] = min(floyd[s][e], cst);
	}

	Floyd_Warshall();
}
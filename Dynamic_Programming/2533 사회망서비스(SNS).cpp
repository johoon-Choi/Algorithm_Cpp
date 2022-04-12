#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> arr;
vector<vector<int>> dp;
vector<bool> visit;
int n, root = 1;

// dp[idx][0] : idx'th node 가 얼리가 아닐 때
//				idx'th node 를 root node 로 잡은
//				Sub tree 의 얼리 개수
// dp[idx][1] : idx'th node 가 얼리일 때
//				idx'th node 를 root node 로 잡은
//				Sub tree 의 얼리 개수

void dfs(int idx) {
	visit[idx] = true;
	dp[idx][1] = 1;

	int size = arr[idx].size();
	for (int i = 0; i < size; i++) {
		int nxt_idx = arr[idx][i];
		if (visit[nxt_idx]) continue;
		dfs(nxt_idx);
		dp[idx][0] += dp[nxt_idx][1];
		// 현재 Node 가 얼리가 아닌 경우엔 아래 자식들이 모두 얼리여야 한다.
		dp[idx][1] += min(dp[nxt_idx][0], dp[nxt_idx][1]);
		// 현재 Node 가 얼리인 경우엔 아래 자식들의 얼리 여부는 상관 없으므로
		//   아래 자식들이 얼리인 경우, 아닌 경우 중 작은 값을 더하게 된다.
	}
}

int main() {
	cin >> n;
	arr.resize(n + 1);
	visit.assign(n + 1, false);
	dp.assign(n + 1, vector<int>(2, 0));

	int u, v;
	for (int i = 1; i < n; i++) {
		cin >> u >> v;
		arr[u].push_back(v);
		arr[v].push_back(u);
	}

	dfs(root);

	cout << min(dp[root][0], dp[root][1]);
}

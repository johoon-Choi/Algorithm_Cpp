#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<int> coins;
vector<vector<int>> dp;

int solve() {
	for (int v = 1; v <= k; v++)
		if (coins[0] <= v && !(v % coins[0])) dp[0][v] += 1;

	for (int i = 1; i < n; i++) {
		for (int v = 1; v <= k; v++) {
			if (coins[i] > v) {
				dp[1][v] = dp[0][v];
			}
			else {// coins[i] <= v
				if (!(v % coins[i])) dp[1][v] += 1; // coins[i] only
				dp[1][v] += dp[0][v]; // except coins[i]

				for (int k = v - coins[i]; k > 0; k -= coins[i]) {
					dp[1][v] += dp[0][k];
				}
			}
		}
		dp[0] = dp[1];
		dp[1].clear();
		dp[1].resize(k + 1);
	}

	return dp[0][k];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> k;
	coins.resize(n);
	dp.assign(2, vector<int>(k + 1, 0));
	// dp[i][v] = i'th 동전까지 고려할 때 v 가치의 경우의 수.

	for (auto& e : coins) cin >> e;

	cout << solve();
}

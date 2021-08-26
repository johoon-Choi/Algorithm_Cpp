#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> tree;
vector<int> List;
vector<int> ans;
int n, m;

int query(int curNode, int left, int right, const int tarLeft, const int tarRight, const int tar) {
	if (tarRight < left || right < tarLeft) return 0;
	if (tarLeft <= left && right <= tarRight)
		return tree[curNode].end() - upper_bound(tree[curNode].begin(), tree[curNode].end(), tar);

	int leftNode = curNode << 1;
	int rightNode = leftNode + 1;
	int mid = (left + right) >> 1;

	return (query(leftNode, left, mid, tarLeft, tarRight, tar)
		+ query(rightNode, mid + 1, right, tarLeft, tarRight, tar));
}

void update(int curNode, int left, int right, const int idx, const int val) {
	tree[curNode].push_back(val);

	if (right <= left) return;

	int mid = (left + right) >> 1;
	int leftNode = curNode << 1;
	int rightNode = leftNode + 1;

	if (idx <= mid) { // -> go left side
		update(leftNode, left, mid, idx, val);
	}
	else { // if (mid < idx) -> go right side
		update(rightNode, mid + 1, right, idx, val);
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;

	List.assign(n + 1, 0);
	tree.resize(4 * n);

	for (int i = 1; i <= n; i++) {
		cin >> List[i];

		update(1, 1, n, i, List[i]);
	}

	for (int i = 1; i < 4 * n; i++)
		sort(tree[i].begin(), tree[i].end());

	cin >> m;

	int s, e, tar;

	while (m--) {
		cin >> s >> e >> tar;

		ans.push_back(query(1, 1, n, s, e, tar));
	}

	for (auto e : ans) cout << e << '\n';
}
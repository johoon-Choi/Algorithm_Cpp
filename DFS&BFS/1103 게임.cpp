#include <iostream>
#include <queue>

#define N 51
#define hole 'H'
#define INF 999'999'999

using namespace std;

typedef struct pos {
	int r, c;
	int val = 0;
} pos;

char arr[N][N];
int dp[N][N];
int h, w;
int maxVal = 0;

const int dr[4] = { 0, 0, 1, -1 };
const int dc[4] = { 1, -1, 0, 0 };

inline bool isSafe(const int& r, const int& c) {
	return 1 <= r && r <= h && 1 <= c && c <= w;
}

bool visit[N][N];

int solve2(const int& r, const int& c, const int& val) {
	int dist = int(arr[r][c] - '0');
	visit[r][c] = true;

	for (int d = 0; d < 4; d++) {
		int nr = r + dr[d] * dist;
		int nc = c + dc[d] * dist;

		if (isSafe(nr, nc) && arr[nr][nc] != hole) {
			if (visit[nr][nc]) return INF;
			if (dp[nr][nc] < val + 1) {
				dp[nr][nc] = val + 1;
				::maxVal = max(::maxVal, solve2(nr, nc, val + 1));
			}
		}
		else ::maxVal = max(::maxVal, val + 1);
	}
	visit[r][c] = false;
	return ::maxVal;
}

int main() {
	cin >> h >> w;

	string input;
	for (int i = 1; i <= h; i++) {
		cin >> input;
		for (int j = 1; j <= w; j++)
			arr[i][j] = input[j - 1];
	}

	int answer = solve2(1, 1, 0);
	cout << (answer == INF ? -1 : answer);
}

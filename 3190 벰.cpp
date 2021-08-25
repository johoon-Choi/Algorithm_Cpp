#include <iostream>
#include <vector>
#include <queue>
#include <set>
#define ground -1
#define row first
#define col second

using namespace std;
typedef pair<int, int> pii;
typedef pair<int, char> pic;

enum {
	Right = 0, Down, Left, Up
};

struct SNAKE {
	int r, c;
	int time;
};

struct comp {
	bool operator()(SNAKE A, SNAKE B) {
		return A.time > B.time; // 시간이 작은 얘들 먼저 빠지도록
	}
};

struct comp2 {
	bool operator()(pic a, pic b) {
		return a.first > b.first;
	}
};

priority_queue<SNAKE, vector<SNAKE>, comp> pq;
priority_queue<pii, vector<pii>, comp2> check;
vector<vector<int>> board;
set<pii> s;
int n, apple, snake;

bool isSafe(int r, int c) {
	return r && c && r <= n && c <= n;
}

int solve(int r, int c, int dir, int tm) {
	if (s.count({ r, c })) return tm; // 몸과 닿았다면 End
	if (!isSafe(r, c)) return tm; // 벽과 닿았다면 End

	int nextDir = dir;

	if (board[r][c] == ground) { // 사과가 없으므로 꼬리를 줄인다.
		SNAKE cur = pq.top();
		s.erase(s.find({ cur.r, cur.c }));
		pq.pop();
	}
	else if (board[r][c] == 1) board[r][c] = ground;
	// 사과가 있으므로, 꼬리를 줄이지 않고 사과를 먹는다(없앤다).

	s.insert({ r, c }); // 현재 위치로 뱀을 늘린다.
	pq.push({ r, c, tm });

	if (!check.empty() && tm == check.top().first){
		char dr = check.top().second;
		if (dr == 'D') nextDir = (dir + 1) % 4;
		else if (dr == 'L') nextDir = ((4 + dir) - 1) % 4;
		check.pop();
	}

	if (nextDir == Up) return solve(r - 1, c, Up, tm + 1);
	else if (nextDir == Down) return solve(r + 1, c, Down, tm + 1);
	else if (nextDir == Left) return solve(r, c - 1, Left, tm + 1);
	else return solve(r, c + 1, Right, tm + 1);
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	cin >> n;

	board.assign(n + 1, vector<int>(n + 1, ground));

	cin >> apple;
	int r, c;
	for (int i = 0; i < apple; i++) {
		cin >> r >> c;

		board[r][c] = 1; // 사과가 있는 위치를 1로 초기화
	}

	cin >> snake;

	int t; char dr;
	for (int i = 0; i < snake; i++) {
		cin >> t >> dr;

		check.push({ t, dr });
	}

	s.insert({ 1, 1 }); // 출발지점에 뱀을 둔다.
	pq.push({ 1, 1, 0 }); // 출발지점을 pq에 push 한다.

	cout << solve(1, 2, Right, 1);
}
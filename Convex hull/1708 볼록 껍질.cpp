#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stack>
#define RIGHT -1
#define LINE 0
#define LEFT 1

using namespace std;

typedef long long LL;

struct point {
	LL x, y;
};

int N;
point sp;
vector<point> arr;
stack<point> s;

LL CCW(point A, point B, point C) {
	LL temp  = (A.x * B.y) + (B.x * C.y) + (C.x * A.y);
	   temp -= (A.x * C.y) + (B.x * A.y) + (C.x * B.y);

	if (temp > 0)	return LEFT;
	else if (!temp) return LINE;
	else			return RIGHT;
}

bool comp1(const point& A, const point& B) { // ORDER BY y ASC, x ASC
	if (A.y != B.y) return A.y < B.y;
	else			return A.x < B.x;
}

bool comp2(const point& A, const point& B) {
	LL dir = CCW(sp, A, B);
	if (dir)	return dir == LEFT;
	else		return comp1(A, B); // 일직선상인 경우?
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
	cin >> N;

	LL input_x, input_y;
	for (int i = 0; i < N; i++) {
		cin >> input_x >> input_y;
		arr.push_back({ input_x, input_y });
	} 

	sort(arr.begin(), arr.end(), comp1);
	sp = arr[0];
	sort(arr.begin() + 1, arr.end(), comp2);

	//arr.push_back(sp);

	// Convex hull 본격적으로 시작!
	point p1, p2, p3;
	p1 = sp;		s.push(p1);
	p2 = arr[1];	s.push(p2);

	for (int i = 2; i < N; i++) {
		p3 = arr[i];
		
		while (1 < s.size()) {
			p2 = s.top();	s.pop();
			p1 = s.top();

			if (CCW(p1, p2, p3) == LEFT) {
				s.push(p2);
				break;
			}
		}
		s.push(p3);
	}

	cout << s.size();
}

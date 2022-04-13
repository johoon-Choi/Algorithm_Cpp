#include <iostream>
#include <cmath>
#include <string>

using namespace std;
typedef unsigned long long ull;

ull n;
ull POWER[10];
ull ans[10] = { 0, };
int p = 0;
bool isNine = false;

void printAns() { // 최종적으로 정답을 프린트
	for (int i = 0; i < 10; i++) cout << ans[i] << ' ';
}

void first_area() {
	ull p2 = p - ull(isNine? 0 : 1);			// n이 9로만 이루어진 경우가 아니면	
												//   first area 에서 숫자의 최대 길이는 p - 1 이다.
	for (int i = 0; i < p2; i++) {				// 
		for (int i = 0; i < 10; i++)
			ans[i] += POWER[p2 - 1];
		ans[0] -= POWER[i];
	}

}

void mid_area(int k) {
	n /= 10;

	for (int i = 0; i < 10; i++)
		ans[i] += (n - POWER[p - (k + 1)] + 1) * POWER[k - 1];
}

void last_area(int k) {
	while ((n % 10) != 9) {						// 첫째자리 수가 1이 될 때 까지
		string cur = to_string(n--);			//   n 값을 줄이면서
		for (int s = 0; s < cur.length(); s++)	//   줄이는 과정중의 n 값들은 하나하나
			ans[cur[s] - '0'] += POWER[k - 1];	//   숫자를 체크해서 집어넣는다.
	}
}

void init() {
	cin >> n;

	POWER[0] = 1;	// POWER array 에 대한 정의 ( POWER[k] == 10 ^ k )
	for (int i = 1; i < 10; i++) POWER[i] = POWER[i - 1] * 10;

	p = to_string(n).length();	// n의 길이(자리수)

	if (p < to_string(n + 1).length()) isNine = true;	// n에 1을 더했더니 숫자 길이가 바뀌는 경우는
}														//   n이 9로만 이루어진 숫자이다.

int main() {
	init();

	if (n < 10) { // n 이 10 미만인 경우 이 if문 안에서 끝난다.
		for (int i = n; 1 <= i; i--)
			ans[i] = 1;
		printAns();

		return 0;
	}

	int k = 1;

	first_area();

	if (!isNine) {
		for (; k <= p - 1; k++) {
			last_area(k);
			mid_area(k);
		}

		for (int i = 1; i <= n; i++)
			ans[i] += POWER[k - 1];
	}

	printAns();
}

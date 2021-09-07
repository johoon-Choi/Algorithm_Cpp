#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<short>> dp;
short answer = 0;

short MAX(short a, short b) {
	if (a > b) return a;
	else return b;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	string s1, s2;
	cin >> s1 >> s2;

	short s1Len = s1.length();
	short s2Len = s2.length();

	dp.assign(s1Len, vector<short>(s2Len, 0));\

	for (int i = 0; i < s2Len; i++)
		if (s1[0] == s2[i]) {
			for (int j = i; j < s2Len; j++) {
				if (s1[0] == s2[j]) dp[0][j] = 1;

				dp[0][j] = 1;
			}
			break;
		}

	for (int i = 0; i < s1Len; i++)
		if (s1[i] == s2[0]) {
			for (int j = i; j < s1Len; j++) {
				if (s1[i] == s2[0]) dp[j][0] = 1;

				dp[j][0] = 1;
			}
			break;
		}

	for (int i = 1; i < s1Len; i++) {
		for (int j = 1; j < s2Len; j++) {
			if (s1[i] == s2[j])
				if (dp[i - 1][j - 1])
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else // 새로운 단어의 시작
					dp[i][j] = 1;

			::answer = MAX(::answer, dp[i][j]);
		}
	}

	cout << ::answer;
}

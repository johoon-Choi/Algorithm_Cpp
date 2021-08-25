#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int score[9] = { 0, 0, 0, 1, 1, 2, 3, 5, 11 };
const int dR[8] = { 1, -1, 0, 0, 1, 1, -1, -1 };
const int dC[8] = { 0, 0, 1, -1, 1, -1, 1, -1 };

int scoreTemp = 0, countTemp = 0;
string wordTemp = "";

struct answer {
	int maxScore;
	string longestWord;
	int numCount;
};

class Node {
public:
	Node* child[26];
	bool isEnd;
	bool isUsed;
	string thisWord;

	Node() : isEnd(false), isUsed(false), thisWord("") {
		for (int i = 0; i < 26; i++)
			child[i] = NULL;
	}
};

class Tri {
public:
	Node* root = new Node;

	void push(string& str) {
		insert(str, 0, root);
	}

	void insert(string& str, int idx, Node* curNode) {
		if (str.length() <= idx) {
			curNode->isEnd = true;
			curNode->thisWord = str;
			return;
		}
		if (curNode->child[str[idx] - 'A'] == NULL) curNode->child[str[idx] - 'A'] = new Node;

		insert(str, idx + 1, curNode->child[str[idx] - 'A']);
	}

	void resetIsEndAndIsUsed(Node* curNode) {
		for (int i = 0; i < 26; i++) {
			if (curNode->child[i] != NULL) {
				resetIsEndAndIsUsed(curNode->child[i]);
				curNode->child[i]->isUsed = false;
			}
		}
		curNode->isUsed = false;
	}
};

vector<string> words;
vector<answer> ans;
int wordSize, tc;

vector<vector<bool>> isVisited;
Tri* TriList = new Tri;

bool isSafe(int row, int col) {
	return 0 <= row && 0 <= col && row < 4 && col < 4;
}

void dfs(vector<string>& board, int row, int col, Node* curNode) {
	isVisited[row][col] = true;

	if (curNode->isEnd && (curNode->isUsed == false)) { // 이 노드를 마지막으로 단어 하나가 생성이 되었으면서
														//   한번도 찾지 못 했던 단어일 때
		curNode->isUsed = true;
		string word = curNode->thisWord;

		::scoreTemp += score[word.length()];
		::countTemp++;
		if (wordTemp.length() < word.length())
			wordTemp = word;
		else if (wordTemp.length() == word.length())
			wordTemp = (wordTemp < word ? wordTemp : word);
	}
	for (int d = 0; d < 8; d++) {
		int nR = row + dR[d];
		int nC = col + dC[d];

		if (isSafe(nR, nC)) { // 다음도 안전할 때
			if (!isVisited[nR][nC] && curNode->child[board[nR][nC] - 'A'] != NULL)
				dfs(board, nR, nC, curNode->child[board[nR][nC] - 'A']);
		}
	}

	isVisited[row][col] = false;
}

void find(vector<string>& board, int row, int col) {
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (TriList->root->child[board[r][c] - 'A'] != NULL) {
				dfs(board, r, c, TriList->root->child[board[r][c] - 'A']);
			}
			isVisited.clear();
			isVisited.assign(4, vector<bool>(4, 0));
		}
	}
}

int main() {
	cin >> wordSize;
	words.assign(wordSize, "");

	isVisited.assign(4, vector<bool>(4, false));

	for (int i = 0; i < wordSize; i++) {
		cin >> words[i];
		TriList->push(words[i]);
	}

	cin >> tc;

	while (tc--) {
		vector<string> board(4);

		for (int i = 0; i < 4; i++) cin >> board[i];

		find(board, 0, 0);

		ans.push_back({ scoreTemp, wordTemp, countTemp });

		::scoreTemp = 0;
		::countTemp = 0;
		::wordTemp = "";
		TriList->resetIsEndAndIsUsed(TriList->root);
	}

	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i].maxScore << ' ' << ans[i].longestWord << ' ' << ans[i].numCount << '\n';
	}
}
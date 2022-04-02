#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;

class Node {
public:
	Node* child[26];
	char curWord;
	int childCnt;
	bool isEnd;

	Node() : curWord('.'), childCnt(0), isEnd(false) {
		for (int i = 0; i < 26; i++)
			child[i] = NULL;
	}
};

class Tri {
public:
	Node* root = new Node;
	int cntSum;

	Tri() : cntSum(0) {};
	~Tri() {
		Delete(root);
	}

	void push(string& str) {
		insert(str, 0, root, NULL);
	}

	int check() {
		check_in(root, 0);
		return cntSum;
	}

private:
	void insert(string& str, int index, Node* curNode, char CUR_WORD) {
		curNode->curWord = CUR_WORD;
		if (str.length() == index) {
			curNode->isEnd = true;
			return;
		}

		char nextWord = str[index];

		if (curNode->child[nextWord - 'a'] == NULL) {	// child Node 없는 경우
			curNode->childCnt++;						// child count 증가시키고
			curNode->child[nextWord - 'a'] = new Node;	// memory 할당
		}

		insert(str, index + 1, curNode->child[nextWord - 'a'], nextWord);
	}

	void check_in(Node* curNode, int cnt) {
		if (curNode->isEnd) {
			if (curNode->childCnt) { // 여기에서 끝나는 단어가 있으면서 다음 단어 있을 때
				cntSum += cnt;
				for (int i = 0; i < 26; i++) {
					if (curNode->child[i] != NULL)
						check_in(curNode->child[i], cnt + 1);
				}
			}
			else cntSum += cnt;
			return;
		}

		for (int i = 0; i < 26; i++) {
			if (curNode->child[i] != NULL)
				check_in(curNode->child[i], cnt + (curNode == root? 1 : (1 < curNode->childCnt ? 1 : 0)));
		}
	}

	void Delete(Node* curNode) {
		for (int i = 0; i < 26; i++) {
			if (curNode->child[i] != NULL)
				Delete(curNode->child[i]);
		}
		delete curNode;
	}
};

int main() {
	cout << fixed;
	cout.precision(2);

	string str;
	while (cin >> n) {
		Tri* tri = new Tri;

		for (int i = 0; i < n; i++) {
			cin >> str;

			tri->push(str);
		}

		int sum = tri->check();
		cout << double(sum) / double(n) << '\n';

		delete tri;
	}
}

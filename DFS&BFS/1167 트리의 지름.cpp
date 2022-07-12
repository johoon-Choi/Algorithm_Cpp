#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
typedef pair<int, int> pii;

int n;
int maxVal = 0;
int maxNode = 0;
vector<pii> nodes[100001];
bool visit[100001];

void dfs(int bef, int cur, int val = 0) {
    visit[cur] = true;

    if (maxVal < val) {
        maxVal = val;
        maxNode = cur;
    }

    for (int i = 0; i < nodes[cur].size(); i++) {
        int nxt = nodes[cur][i].first;

        if (!visit[nxt])
            dfs(cur, nxt, val + nodes[cur][i].second);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n;

    int cur = 0;
    int nxt = 0;
    int dis = 0;

    for (int i = 1; i <= ::n; i++) {
        cin >> cur;

        while (cin >> nxt && nxt != -1) {
            cin >> dis;
            nodes[cur].push_back(pii(nxt, dis));
        }
    }

    dfs(0, 1);
    memset(visit, false, 100001);
    dfs(0, maxNode);

    cout << ::maxVal;
}

#include <vector>
#include <string>

using namespace std;

inline string erase(string str, int start, int area) {
	return str.substr(0, start) + str.substr(start + area, str.length() - start - area);
}

string solution(string id) {
	for (int i = 0; i < id.length(); i++) {
		if ('A' <= id[i] && id[i] <= 'Z') id[i] += 32;
		else if ((id[i] < '0' || '9' < id[i]) && (id[i] < 'a' || 'z' < id[i]) && id[i] != '-' && id[i] != '_' && id[i] != '.')
			id = erase(id, i--, 1);
		else if (id[i] == '.' && 1 <= i && id[i - 1] == '.')
			id = erase(id, i--, 1);
	}

	while (id.length() && id[0] == '.') id = id.substr(1);
	while (id.length() && id[id.length() - 1] == '.') id.pop_back();

	if (id.length() == 0) id = "a";

	if (16 <= id.length()) id = id.substr(0, 15);
	while (id.length() && id[id.length() - 1] == '.') id = id.substr(0, id.length() - 1);

	while (id.length() <= 2) id += id[id.length() - 1];
	
	return id;
}

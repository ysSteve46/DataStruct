//hw 1-2: powersets
//41143146
#include <iostream>

using namespace std;

/*
* for a set with 2 elements, there will be 4 possible sets
* for a set with 3 elements, there will be 8 possible sets
* for a set with 4 elements, there will be 16 possible sets
* steps taken: pow(2, n), n = elements
* time complexity: O(2^n)
*/

void powerset(string set, int index, string cur) {
	int n = set.length(); //the case to end recursion

	if (index == n) {
		if (cur.length() < 1) {
			cout << "(),";
		}
		else {
			cout << "(";
			for (int i = 0; i < cur.length(); i++) {
				cout << cur[i] << ",";
			}
			cout << "\b),";
		}
		return;
	}
	
	//consider the character as part of current subset
	powerset(set, index + 1, cur + set[index]);
	//the current character is not a part of current subset
	powerset(set, index + 1, cur);
}

int main() {
	int n;
	cin >> n;
	//this shows the set S
	string s = "";
	cout << "Set S = (";
	for (int i = 0; i < n; i++) {
		s += 'a' + i;
		cout << s[i] << ',';
	}
	cout << "\b)\n";
	//the powerset of S
	cout << "Powerset of S:\n";
	powerset(s, 0, "");
	cout << "\b \n";

	return 0;
}
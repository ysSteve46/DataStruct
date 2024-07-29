//hw 1-2: powersets
//41143146
#include <iostream>
#include <string>

using namespace std;

/*
* for a set with 2 elements, there will be 4 possible sets
* for a set with 3 elements, there will be 8 possible sets
* for a set with 4 elements, there will be 16 possible sets
* steps taken: pow(2, n), n = elements
* time complexity: O(log2n)
*/

void showSet(char* set, int elems, int items) {
	if (elems == 0) {
		cout << "()";
	}else {
		//ex: set (a,b,c)
		//for sets with 2 elements, this loop finds (a,b),(a,c) first, then (b,c)
		int cur = 0; //current element
		while (cur <= items - elems) {
			cout << "(";
			for (int i = cur; i < cur + elems; i++) {
				cout << set[i] << ",";
			}
			cout << "\b),";
			cur++;
		}
		cout << "\b";
	}
	cout << ",";
	//powerset(set, elems+1, items);
}

void powerset(char* set, int start, int end) {
	if (start == end) {
		//print the final set contain every element, ending recursion
		cout << "(";
		for (int i = 0; i < end; i++) {
			cout << set[i] << ',';
		}
		cout << "\b)\n";
	}
	else {
		//get sets with elements equal to start value per recursion
		showSet(set, start, end);
		powerset(set, start + 1, end);
	}
}

int main() {
	int n;
	cin >> n;
	//this shows the set S
	char* s = new char[n];
	cout << "Set S = (";
	for (int i = 0; i < n; i++) {
		s[i] = 'a' + i;
		cout << s[i] << ',';
	}
	cout << "\b)\n";
	//the powerset of S
	//int x = pow(2, sizeof(s));
	powerset(s, 0, n);

	return 0;
}
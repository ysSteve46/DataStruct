//hw 1-2: powersets
//41143146
#include <iostream>
#include <cmath>

using namespace std;

/*
* for a set with 2 elements, there will be 4 possible sets
* for a set with 3 elements, there will be 8 possible sets
* for a set with 4 elements, there will be 16 possible sets
* steps taken: pow(2, n), n = elements
* time complexity: O(2^n)
*/

int fact(int n) {
	if (n <= 1) return 1;
	else return n * fact(n - 1);
}

void showSet(char* set, int elems, int items) {
	if (elems == 0) {
		cout << "()";
	}else {
		int ps = fact(items) / (fact(elems)*fact(items-elems)); //C(m,n)
		//ex: set (a,b,c)
		//for sets with 2 elements, this loop finds (a,b),(a,c) first, then (b,c)
		int cur; //current element
		for (cur = 0; cur < ps; ++cur) {
			cout << "(";
			for (int i = 0; i < items; ++i) {
				// Check if the i-th bit in cur is set
				if (cur & i) {
					cout << set[i] << ",";
				}
			}
			cout << "\b),";
		}
	}
	cout << ",";
}

void powerset(char* set, int elems, int len) {
	if (elems == len) {
		//print the final set contain every element, ending recursion
		cout << "(";
		for (int i = 0; i < len; i++) {
			cout << set[i] << ',';
		}
		cout << "\b)\n";
	}
	else {
		//get sets with elements equal to elems value per recursion
		showSet(set, elems, len);
		powerset(set, elems + 1, len);
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
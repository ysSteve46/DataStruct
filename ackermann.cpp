//hw1-1: Ackermann
//41143146
#include <iostream>
#include <stack>

using namespace std;

//recursion
int ackermann(int m, int n) {
    if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        return ackermann(m-1, 1);
    }
    else {
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}

//non recursion
int ackermann2(int m, int n) {
    stack<int> mstk;
    stack<int> nstk;
    mstk.push(m);
    nstk.push(n);

    while (!mstk.empty()) {
        m = mstk.top();
        n = nstk.top();
        mstk.pop(); nstk.pop();

        if (m == 0) {
            n++;
            if (!mstk.empty()) nstk.top() = n;
        }
        else if (m > 0 && n == 0) {
            mstk.push(m - 1);
            nstk.push(1);
        }
        else if (m > 0 && n > 0) {
            mstk.push(m - 1);
            nstk.push(-1);
            mstk.push(m);
            nstk.push(n - 1);
        }
        else if (n == -1) {
            n++;
            if (!mstk.empty()) nstk.top() = n;
        }
    }
    return n;
}

int main(){
    int x, y;
    cin >> x >> y;
    cout << "recursion: " << ackermann(x, y) << '\n';
    cout << "non-recursion: " << ackermann2(x, y) << '\n';

    return 0;
}
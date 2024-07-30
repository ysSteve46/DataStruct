//hw1-1: Ackermann
//41143146
#include <iostream>

//array size for non recursive algorithm
#define ARRAY_SIZE 1000

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
    int ack[ARRAY_SIZE][2];
    int top = 0;
    
    //initialize
    ack[top][0] = m;
    ack[top][1] = n;
    top++;

    //simulate each state
    while (top > 0) {
        //pop the top state
        top--;
        m = ack[top][0];
        n = ack[top][1];

        if (m == 0) {
            n = n + 1;
            if (top > 0) {
                //update the slot below the top
                ack[top - 1][1] = n;
            }
        }
        else if (n == 0) {
            //add (m-1,1)
            ack[top][0] = m - 1;
            ack[top][1] = 1;
            top++;
        }
        else if (n > 0 && m > 0) {
            //add (m-1, -1) and (m,n-1), where -1 is the marker
            ack[top][0] = m - 1;
            ack[top][1] = -1;
            top++;
            ack[top][0] = m;
            ack[top][1] = n - 1;
            top++;
        }
        else {
            //updates when n < 0
            n++;
            if (top > 0) {
                //update the slot below the top
                ack[top - 1][1] = n;
            }
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
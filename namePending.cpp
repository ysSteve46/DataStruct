#include <iostream>
#include <cmath>

using namespace std;

int main(){
  int arr[2][10] = {{1,4,5,6,8,9,2,3,11,7},{22,3,10,24,15,17,5,20,1,30}};
  int month,date,mdiff,daydiff,totaldiff=99,person=0;
  cin >> month >> date;
  for(int i=0; i<10; i++){
    mdiff=abs(month-arr[0][i]);
    daydiff=abs(date-arr[1][i]);
    if(totaldiff>(mdiff+daydiff)){
      totaldiff=mdiff+daydiff;
      person=i;
    }
  }
  cout <<　"The person's birthday close to this date is person " << person+1 << '\n';

  return 0;
}

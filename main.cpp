#include <iostream>
#include <vector>
using namespace std;

#define DEBUG

int getArrayMinNum(const vector<int> &list) { //Returm most minimum num from array
  vector<int> sums(list.size(), 0);
  for (int i : list)
    sums[i - 1]++;

  for (int i = 0; i < sums.size(); i++) {
    if (4 > sums[i]) { // 4 is max duplicate card nums
      return i+1;
    }
  }

  return -1;
}

bool isArrayCorrect(vector<int> &list) {
  vector<int> sums(list.size(), 0);
  for (int i : list)
    sums[i - 1]++;

  for (int i : sums)
    if (4 < i)
      return false;

  return true;
}

bool arrayUpdate(vector<int> &list) { //Update array and return false if can't(end)
  do {
    list[list.size() - 1]++;
  }while (!isArrayCorrect(list));

  for (int i = list.size() - 1; i > 0; i--){
    if (13 < list[i]) {
      list[i] = getArrayMinNum(list);
      list[i-1]++;
    } else break;
  }

  return true;
}

void game(vector<int> &list) { //Excute GAME from array
#ifdef DEBUG
  for (int i : list)
    cout << i << " ";
  cout << "\n";
#endif
}

int main(void) {
  vector<int> list = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4}; //Initial cards
  //vector<int> list = {13, 13, 13, 13, 12, 12, 12, 12, 11, 11, 11, 11, 10, 10, 10}; //Initial cards


  for(int i=0;i<10000000;i++){
    cout<<i<<": ";
    arrayUpdate(list);
    if (isArrayCorrect(list)) {
      cout<<"👍\n";
    } else {
      cout<<"⤵\n";
      game(list);
      return 0;
    }
  }
}

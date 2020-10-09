#include <iostream>
#include <vector>
using namespace std;

#define DEBUG

int getArrayMinNum(const vector<int> &_list) { // Returm most minimum num from array
  vector<int> sums(_list.size(), 0);
  for (int i : _list)
    sums[i - 1]++;

  for (int i = 0; i < sums.size(); i++) {
    if (4 > sums[i]) { // 4 is max duplicate card nums
      return i+1;
    }
  }

  return -1;
}

bool isArrayCorrect(vector<int> &_list) {
  vector<int> sums(_list.size(), 0);
  for (int i : _list) {
    if (!(0 <= i and i <= 13))
      return false;
    sums[i - 1]++;
  }

  for (int i : sums)
    if (4 < i)
      return false;

  return true;
}

bool arrayUpdate(vector<int> &_list,vector<int> &_sums) { // Update array and return false if can't(end)
  _sums[_list[_list.size() - 1] - 1]--;
  _list[_list.size()-1]++;
  _sums[_list[_list.size() - 1] - 1]++;

  for (int i = _list.size() - 1; i > 0; i--) {
    if (13 < _list[i]) {
      _list[i]=getArrayMinNum(_list);
      _list[i-1]++;
    }else break;
  }

  return true;
}

void game(vector<int> &_list) { // Excute GAME from array
#ifdef DEBUG
  for (int i : _list)
    cout << i << " ";
  cout << "\n";
#endif
}

int main(void) {
  vector<int> list = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4}; //Initial cards
  vector<int> sums = {4, 4, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  for(int i=0;i<10000000;i++){
    cout<<i<<": ";
    arrayUpdate(list,sums);
    if (isArrayCorrect(list)) {
      cout<<"👍\n";
      game(list);
    } else {
      cout<<"⤵\n";
      game(list);
      return 0;
    }
  }
}

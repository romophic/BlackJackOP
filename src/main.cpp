#include <cstdint>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
using namespace std;

#define DEBUG

void putArrayNums(vector<int> &_list,string _str) { //put array
#ifdef DEBUG
  cout<<_str<<": ";
  for (int i : _list)
    cout << i << " ";
  cout << "\n";
#endif
}

int getMiniNum(vector<int> &_sum,int _num) {//numを超える最小の設置できる値
  for (int i = _num; i < _sum.size(); i++) {
    if (_sum[i] < 4) {
      return i+1;
    }
  }
  return 14;
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

bool arrayUpdate(vector<int> &_list) { // Update array and return false
                                       // ifcan't(end) _list[_list.size()-1]++;
  vector<int> sums(13, 0);
  for (int i:_list) // kuriagari
    sums[i - 1]++;

  putArrayNums(sums,"  sums");

  sums[_list[_list.size()-1]-1]--;
  _list[_list.size()-1]=getMiniNum(sums,_list[_list.size()-1]);
  sums[_list[_list.size()-1]-1]++;

  for (int i = _list.size() - 1; i > 0; i--) { // kuriagari
    putArrayNums(_list,"    "+to_string(i));
    if (14 <= _list[i]) {
      sums[_list[i]-1]--;
      _list[i]=getMiniNum(sums,0);
      sums[_list[i]-1]++;

      sums[_list[i]-1]--;
      _list[i-1]=getMiniNum(sums,_list[i-1]);
      sums[_list[i]-1]++;
    }
  }

  putArrayNums(_list, "  after_list");
  return true;
}

int main(void) {
  vector<int> list = {1, 1, 1, 1, 2, 2, 2, 2,
                      3, 3, 3, 3, 4, 4, 4}; // Initialcards
  for (int64_t i = 0;; i++) {
    cout<<i<<":\n";
    putArrayNums(list, "  befor_list");
    arrayUpdate(list);
    if (isArrayCorrect(list)) {
    } else {
      cout << "ERR\n";
      return 0;
    }
  }
  cout << "complete\n";
}
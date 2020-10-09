#include <iostream>
#include <vector>
using namespace std;

#define DEBUG

int getArrayMinNum(const vector<int> &list) { //あり得る最小の値を返す
  vector<int> sums(15, 0);
  for (int i : list)
    sums[i - 1]++;

  for (int i = 0; i < sums.size(); i++) {
    if (4 > sums[i]) {
      return i+1;
    }
  }

  return -1;
}

bool arrayUpdate(vector<int> &list) { //手札を更新する もう無ければfalse
  list[list.size() - 1]++;

  if (13 < list[list.size() - 1]) {

  }

  return true;
}

void game(vector<int> &list) { //ゲームの処理
#ifdef DEBUG
  for (int i : list)
    cout << i << " ";
  cout << "\n";
#endif
}

int main(void) {
  vector<int> list = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4}; //初期手札

  for(int i=0;i<10;i++){
    game(list);
  }
}

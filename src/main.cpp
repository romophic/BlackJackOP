#include <cstdint>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>
using namespace std;

/*
int getMiniNum(vector<int> &_sum, int _num) { // numを超える最小の設置できる値
  for (int i = _num; i < _sum.size(); i++) {
    if (_sum[i] < 4) {
      return i + 1;
    }
  }
  return 14;
}

bool isArrayCorrect(vector<int> &_list) { // check array
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
  for (int i : _list) // kuriagari
    sums[i - 1]++;

  sums[_list[_list.size() - 1] - 1]--;
  _list[_list.size() - 1] = getMiniNum(sums, _list[_list.size() - 1]);
  sums[_list[_list.size() - 1] - 1]++;

  for (int i = _list.size() - 1; i > 0; i--) { // kuriagari
    if (14 <= _list[i]) {
      sums[_list[i] - 1]--;
      _list[i] = getMiniNum(sums, 0);
      sums[_list[i] - 1]++;

      sums[_list[i] - 1]--;
      _list[i - 1] = getMiniNum(sums, _list[i - 1]);
      sums[_list[i] - 1]++;
    }
  }

  return true;
}
*/

std::mt19937 mt{std::random_device{}()};
std::uniform_int_distribution<int> dist(1, 13);

void putArrayNums(const vector<int> &_list, const string _str) { // put array
  cout << _str << ": ";
  for (int i : _list)
    cout << i << " ";
  cout << "\n";
}

void arrayFillRandom(vector<int> &_list) { // fill array random num (1 ~ 13)
  vector<int> cnt(13, 0);
  for (int i = 0; i < _list.size();) {
    int num = dist(mt);
    if (cnt[num - 1] < 4) {
      cnt[num - 1]++;
      _list[i] = num;
      i++;
    }
  }
}

namespace status{
  enum GAMESTATUS {
    WIN   = 0,
    LOSE  = 1,
    ERROR = -1
  };
  enum CARDSTATUS{
    HIT = 0,
    STAND = 1,
    DOUBLEDOWN = 2,
    SALENDER = 3
  };
  constexpr int charts[10][10] = {
    {0,0,0,0,0,0,0,0,0,0},
    {0,2,2,2,2,0,0,0,0,0},
    {2,2,2,2,2,2,2,2,0,0},
    {2,2,2,2,2,2,2,2,2,0},
    {0,0,1,1,1,0,0,0,0,0},
    {1,1,1,1,1,0,0,0,0,0},
    {1,1,1,1,1,0,0,0,0,0},
    {1,1,1,1,1,0,0,0,3,0},
    {1,1,1,1,1,0,0,3,3,3},
    {1,1,1,1,1,1,1,1,1,1}
  };
}

int getChooseCard(int _me_sum,int _dealer_opened_card){
  //EDUCATION to me_sum
  if (_me_sum <= 8)
    _me_sum=8;
  if (17 <= _me_sum)
    _me_sum=17;

  //Too
  if (_dealer_opened_card == 1)
    _dealer_opened_card = 11;
  if (10 <= _dealer_opened_card)
    _dealer_opened_card = 10;

  return status::charts[_me_sum-8][_dealer_opened_card-2];
}

int game(const vector<int> &_list) { //code of kernel
  int cardpos=0;
  int me_sum=0;
  int dealer_sum=0;
  vector<int> me, dealer;

  //first hit time x2
  me.push_back(_list[cardpos]);cardpos++;
  me.push_back(_list[cardpos]);cardpos++;
  me_sum+=me[0]+me[1];

  dealer.push_back(_list[cardpos]);cardpos++;
  dealer.push_back(_list[cardpos]);cardpos++;
  dealer_sum+=dealer[0]+dealer[1];

  if(me[0] == me[1]){
    ;//いわゆるスプリット return SPRIT;
  }

  //ディーラーが<17まで引くやつ
  while(true){
    dealer.push_back(_list[cardpos]);cardpos++;
    dealer_sum+=dealer[cardpos-1];

    if(16 < dealer_sum)
      break;
  }

  //Meが引く。オープンカードはdealer.at(0)
  while (true) {
    int meshouldcard=getChooseCard(me_sum,dealer[0]);
    switch (meshouldcard) {
      case status::HIT: {
        me.push_back(_list[cardpos]);cardpos++;
      }
      case status::STAND: {
        goto END;
      }
      case status::DOUBLEDOWN: {
        ;//idk TODO:
      }
      case status::SALENDER: {
        ;//idk TODO:
      }
    }
  }
END: // game of end

  return status::ERROR;
}

int main(void) {
  vector<int> list = {1, 1, 1, 1, 2, 2, 2, 2,
                      3, 3, 3, 3, 4, 4, 4}; // Initialcards
}
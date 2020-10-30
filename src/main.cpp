//   ____  _            _       _            _     ___  ____   //
//  | __ )| | __ _  ___| | __  | | __ _  ___| | __/ _ \|  _ \  //
//  |  _ \| |/ _` |/ __| |/ /  | |/ _` |/ __| |/ / | | | |_) | //
//  | |_) | | (_| | (__|   < |_| | (_| | (__|   <| |_| |  __/  //
//  |____/|_|\__,_|\___|_|\_\___/ \__,_|\___|_|\_\\___/|_|     //
//                      Made by NULLCT                         //

#include <condition_variable>
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

//generate random num
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

namespace status{ //game status
  enum GAMESTATUS { //game results
    WIN   = 0,
    LOSE  = 1,
    DRAW = 2,
    ERROR = -1
  };
  enum CARDSTATUS{ //card tyoes
    HIT = 0,
    STAND = 1,
    DOUBLEDOWN = 2,
    SALENDER = 3
  };
  constexpr int chart_first[10][10] = { //first chart
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
  constexpr int chart_plusa[8][10] = { //if include ace
    {0,0,0,2,2,0,0,0,0,0},
    {0,0,0,2,2,0,0,0,0,0},
    {0,0,0,2,2,0,0,0,0,0},
    {0,0,2,2,2,0,0,0,0,0},
    {0,0,2,2,2,0,0,0,0,0},
    {0,2,2,2,2,0,0,0,0,0},
    {1,2,2,2,2,1,1,0,0,0},
    {1,1,1,1,1,1,1,1,1,1}
  };
  constexpr int chart_second[7][10] = { // in second time
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,0,0,0,0,0},
    {1,1,1,1,1,0,0,0,0,0},
    {1,1,1,1,1,0,0,0,0,0},
    {1,1,1,1,1,0,0,0,0,0},
    {1,1,1,1,1,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1}
  };
  constexpr int chart_seconda[3][10] = { // in secon if include ace
    {0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,0,0,0},
    {1,1,1,1,1,1,1,1,1,1}
  };
}

int getChooseCardFromFirst(int _me_sum, int _dealer_opened_card) { // Choose card from chart_first
  // EDUCATION to me_sum
  if (_me_sum <= 8)
    _me_sum=8;
  if (17 <= _me_sum)
    _me_sum=17;

  //Too
  if (_dealer_opened_card == 1)
    _dealer_opened_card = 11;
  if (10 <= _dealer_opened_card)
    _dealer_opened_card = 10;

  return status::chart_first[_me_sum-8][_dealer_opened_card-2];
} // done!
int getChooseCardFromFirstAce(int _me_sum, int _dealer_opened_card) { // Choose card from chart_plusa
  // EDUCATION to me_sum
  if (_me_sum <= 2)
    _me_sum=2;
  if (9 <= _me_sum)
    _me_sum=9;

  //Too
  if (_dealer_opened_card == 1)
    _dealer_opened_card = 11;
  if (10 <= _dealer_opened_card)
    _dealer_opened_card = 10;

  return status::chart_first[_me_sum-2][_dealer_opened_card-2];
} // done!
int getChooseCardFromSecond(int _me_sum, int _dealer_opened_card) { // Choose card from chart_second
  // EDUCATION to me_sum
  if (_me_sum <= 11)
    _me_sum=11;
  if (17 <= _me_sum)
    _me_sum=17;

  //Too
  if (_dealer_opened_card == 1)
    _dealer_opened_card = 11;
  if (10 <= _dealer_opened_card)
    _dealer_opened_card = 10;

  return status::chart_first[_me_sum-11][_dealer_opened_card-2];
}//done!
int getChooseCardFromSecondAce(int _me_sum, int _dealer_opened_card) { // Choose card from chart_second
  // EDUCATION to me_sum
  if (_me_sum <= 7)
    _me_sum=7;
  if (9 <= _me_sum)
    _me_sum=9;

  //Too
  if (_dealer_opened_card == 1)
    _dealer_opened_card = 11;
  if (10 <= _dealer_opened_card)
    _dealer_opened_card = 10;

  return status::chart_first[_me_sum-7][_dealer_opened_card-2];
}//done!

int game(const vector<int> &_list) { // code of kernel
  int cardpos = 0;                   // point of _list[]
  int me_sum = 0, dealer_sum = 0;    // both player's sum
  vector<int> me, dealer;            // Both hand
  bool atr=false;                    // Ace trigger
  bool firsttr=true;

  // first hit time x2
  me.push_back(_list[cardpos]);cardpos++;
  me.push_back(_list[cardpos]);cardpos++;
  me_sum += me[0] + me[1];
  if(me[0] == 1 or me[1] == 1)
    atr=true;

  dealer.push_back(_list[cardpos]);cardpos++;
  dealer.push_back(_list[cardpos]);cardpos++;
  dealer_sum += dealer[0] + dealer[1];

  if (dealer_sum == 21) { // BlackJack!!
    cout<<"BlackJack\n";
    return 0;
  }

  int meshouldcard = 0;
  // Open card is dealer[0]
  while (true) {
    for (int i : me) // put arrays
      cout << i << " ";
    cout<<"\n";

    if (firsttr) {
      firsttr = false;
      if(atr)
        meshouldcard = getChooseCardFromFirstAce(me_sum,dealer[0]);
      else
        meshouldcard = getChooseCardFromFirst(me_sum, dealer[0]);
    } else {
      if(atr)
        meshouldcard = getChooseCardFromSecondAce(me_sum,dealer[0]);
      else
        meshouldcard = getChooseCardFromSecond(me_sum, dealer[0]);
    }

    switch (meshouldcard) {
      case status::HIT:
        me.push_back(_list[cardpos]);cardpos++;
        me_sum += _list[_list.size() - 1];
        if (me[me.size() - 1] == 1)
          atr=true;
        cerr << "Hit: " << me[me.size() - 1] << "\n";
        break;

      case status::STAND:
        goto END;
        break;

      case status::DOUBLEDOWN:; // idk TODO:
        cout<<"DOUBLEDOWN\n";
        me.push_back(_list[cardpos]);cardpos++;
        me_sum += _list[_list.size() - 1];
        if (me[me.size() - 1] == 1)
          atr=true;
        cerr << "Hit: " << me[me.size() - 1] << "\n";
        goto END;

      case status::SALENDER:; // idk TODO:
        cout<<"DOUBLEDOWN\n";
        goto END;

      default:
        cout << "something error\n";
        goto END;
    }
  }
END: // game of end

  // dealer take card while ($sum < 17)
  while(true){
    dealer.push_back(_list[cardpos]);cardpos++;
    dealer_sum += dealer[dealer.size() - 1];

    if(16 < dealer_sum)
      break;
  }

  // put hands
  cout << "Results:\n  Me:\n    ";
  for (int i : me)
    cout << i << " ";
  cout << "\n  Dealer:\n    ";
  for (int i : dealer)
    cout << i << " ";
  cout << "\n";

  if(atr and me_sum+10 <= 21)
    me_sum+=10;

  if (me_sum < dealer_sum) {
    return status::LOSE;
  } else if (me_sum > dealer_sum) {
    return status::WIN;
  } else {
    return status::DRAW;
  }

  return status::ERROR;
}

int main(void) {
  vector<int> list = {1, 7, 2, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5}; // Initialcards
  switch (game(list)) {
  case status::WIN:
    cout<<"WIN\n";
    break;

  case status::LOSE:
    cout<<"LOSE\n";
    break;

  case status::DRAW:
    cout<<"DRAW\n";
    break;
  }
}
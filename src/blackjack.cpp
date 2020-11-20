//TODO:ブラックジャックの1
//   ____  _            _       _            _     ___  ____   //
//  | __ )| | __ _  ___| | __  | | __ _  ___| | __/ _ \|  _ \  //
//  |  _ \| |/ _` |/ __| |/ /  | |/ _` |/ __| |/ / | | | |_) | //
//  | |_) | | (_| | (__|   < |_| | (_| | (__|   <| |_| |  __/  //
//  |____/|_|\__,_|\___|_|\_\___/ \__,_|\___|_|\_\\___/|_|     //
//                      Made by NULLCT                         //
#pragma once

#include <iostream>
#include <vector>
using namespace std;

namespace gamestatus {
enum GAMESTATUS { // game results
  WIN = 0,
  LOSE = 1,
  DRAW = 2,
  DOUBLEDOWNTOWIN = 3,
  DOUBLEDOWNTOLOSE = 4,
  DOUBLEDOWNTODRAW = 5,
  SALENDER = 6,
  BLACKJACK = 7,
  ERROR = -1
};
}
namespace cardstatus {
enum CARDSTATUS { // card tyoes
  HIT = 0,
  STAND = 1,
  DOUBLEDOWN = 2,
  SALENDER = 3
};
}
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
constexpr int chart_firsta[8][10] = { //if include ace
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

int getChooseCardFromFirst(int _me_sum, int _dealer_opened_card) { // Choose card from chart_first
  // EDUCATION to me_sum
  if (_me_sum <= 8)
    _me_sum = 8;
  if (17 <= _me_sum)
    _me_sum = 17;

  // Too
  if (10 <= _dealer_opened_card)
    _dealer_opened_card = 10;
  if (_dealer_opened_card == 1)
    _dealer_opened_card = 11;

  return chart_first[_me_sum - 8][_dealer_opened_card - 2];
}
int getChooseCardFromFirstAce(int _me_sum, int _dealer_opened_card) { // Choose card from chart_plusa
  // EDUCATION to me_sum
  if (_me_sum <= 2)
    _me_sum = 2;
  if (9 <= _me_sum)
    _me_sum = 9;

  // Too
  if (10 <= _dealer_opened_card)
    _dealer_opened_card = 10;
  if (_dealer_opened_card == 1)
    _dealer_opened_card = 11;

  return chart_firsta[_me_sum - 2][_dealer_opened_card - 2];
}
int getChooseCardFromSecond(int _me_sum, int _dealer_opened_card) { // Choose card from chart_second
  // EDUCATION to me_sum
  if (_me_sum <= 11)
    _me_sum = 11;
  if (17 <= _me_sum)
    _me_sum = 17;

  // Too
  if (_dealer_opened_card == 1)
    _dealer_opened_card = 11;
  if (10 <= _dealer_opened_card)
    _dealer_opened_card = 10;

  return chart_second[_me_sum - 11][_dealer_opened_card - 2];
}
int getChooseCardFromSecondAce(int _me_sum, int _dealer_opened_card) { // Choose card from chart_second
  // EDUCATION to me_sum
  if (_me_sum <= 7)
    _me_sum = 7;
  if (9 <= _me_sum)
    _me_sum = 9;

  // Too
  if (10 <= _dealer_opened_card)
    _dealer_opened_card = 10;
  if (_dealer_opened_card == 1)
    _dealer_opened_card = 11;

  return chart_seconda[_me_sum - 7][_dealer_opened_card - 2];
}

void meDraw(vector<int> &me,const vector<int> &_list,int &me_sum,int &cardpos) {
  me.push_back(_list[cardpos]);
  cardpos++;
  me_sum += me[me.size() - 1];
}
void dealerDraw(bool &btr,int &dealer_sum,vector<int> &dealer,const vector<int> &_list,int &cardpos) {
  while(true){
    dealer.push_back(_list[cardpos]);cardpos++;
    dealer_sum += dealer[dealer.size() - 1];
    if(dealer[dealer.size()-1] == 1){ //さっきひいたやつが1なら
      btr=true;
    }
    if(dealer_sum < 17 or (btr and dealer_sum+10 <= 21)){
      break;
    }
  }

  if(btr and dealer_sum+10 <= 21){
    dealer_sum+=10;
  }
}

constexpr int isWinLoseDraw(const int me_sum, const int dealer_sum) {
  if (21 < me_sum and 21 < dealer_sum) {
    return gamestatus::DRAW;
  } else {
    if (21 < me_sum)
      return gamestatus::LOSE;
    if (21 < dealer_sum)
      return gamestatus::WIN;

    if (me_sum == dealer_sum) {
      return gamestatus::DRAW;
    } else {
      if (me_sum < dealer_sum) {
        return gamestatus::LOSE;
      } else {
        return gamestatus::WIN;
      }
    }
  }
  return gamestatus::ERROR;
}

constexpr int isWinLoseDrawInDD(const int me_sum, const int dealer_sum) {
  switch (isWinLoseDraw(me_sum, dealer_sum)) {
  case gamestatus::WIN:
    return gamestatus::DOUBLEDOWNTOWIN;

  case gamestatus::LOSE:
    return gamestatus::DOUBLEDOWNTOLOSE;

  case gamestatus::DRAW:
    return gamestatus::DOUBLEDOWNTODRAW;

  case gamestatus::ERROR:
    return gamestatus::ERROR;

  default:
    return gamestatus::ERROR;
  }
}

int game(const vector<int> &_list) { // code of kernel (0.0000044s)(0.0044ms)
  int cardpos = 0;                   // point of _list[]
  int me_sum = 0, dealer_sum = 0;    // both player's sum
  bool atr = false;                  // Ace trigger
  bool btr = false;
  bool firsttr = true;               // First trigger
  int meshouldcard = 0;              // should to do
  vector<int> me, dealer;            // Both hand

  // first hit time x2
  me.push_back(_list[cardpos]);cardpos++;
  me.push_back(_list[cardpos]);cardpos++;
  me_sum = me[0] + me[1];
  if(me[0] == 1 or me[1] == 1) atr=true;

  dealer.push_back(_list[cardpos]);cardpos++;
  dealer.push_back(_list[cardpos]);cardpos++;
  dealer_sum = dealer[0] + dealer[1];
  if(dealer[0] == 1 or dealer[1] == 1) btr=true;

  if ((me[0] == 1 or me[1] == 1) and me_sum == 11) // BlackJack!!
    return gamestatus::BLACKJACK;

  if ((dealer[0] == 1 or dealer[1] == 1) and dealer_sum == 11) // dealer's BlackJack!!
    return gamestatus::LOSE;

  // DEBUG
  cout<<atr<<" "<<btr<<endl;
  // END DEBUG

  while (true) { // Open card is dealer[0]
    // DEBUG
    cout<<"ME:";
    for (auto i : me)
      cout<<i<<" ";
    cout << "\n" << "Dealer:";
    for (auto i : dealer)
      cout<<i<<" ";
    cout<<"\n";
    // END DEBUG

    if (_list.size() - 1 < cardpos)
      return gamestatus::ERROR;

    if (firsttr) {
      firsttr = false;
      if (atr and 21-10 >= me_sum)
        meshouldcard = getChooseCardFromFirstAce(me_sum, dealer[0]);
      else
        meshouldcard = getChooseCardFromFirst(me_sum, dealer[0]);
    } else {
      if (atr and 21-10 >= me_sum)
        meshouldcard = getChooseCardFromSecondAce(me_sum, dealer[0]);
      else
        meshouldcard = getChooseCardFromSecond(me_sum, dealer[0]);
    }

    switch (meshouldcard) {
    case cardstatus::HIT:
      // DEBUG
      cout<<"HIT\n";
      // END DEBUG
      meDraw(me, _list, me_sum, cardpos);

      if (me[me.size() - 1] == 1)
        atr = true;

      if (21 <= me_sum)
        goto END;
      break;

    case cardstatus::STAND:
      // DEBUG
      cout<<"STAND\n";
      // END DEBUG
      goto END;

    case cardstatus::DOUBLEDOWN: // idk TODO:
      // DEBUG
      cout<<"DOUBLEDOWN\n";
      // END DEBUG
      me.push_back(_list[cardpos]);
      cardpos++;
      me_sum += me[me.size() - 1];

      dealerDraw(btr,dealer_sum, dealer, _list, cardpos);
      // DEBUG
      cout<<"ME:";
      for (auto i : me)
        cout<<i<<" ";
      cout << "\n" << "Dealer:";
      for (auto i : dealer)
        cout<<i<<" ";
      cout<<"\n";
      // END DEBUG
      
      if(atr and me_sum+10 <= 21)
        me_sum+=10;

      return isWinLoseDrawInDD(me_sum, dealer_sum);

    case cardstatus::SALENDER: // idk TODO:
      // DEBUG
      cout<<"SALENDER\n";
      // END DEBUG
      return gamestatus::SALENDER;

    default:
      // DEBUG
      cout<<"ERROR\n";
      // END DEBUG
      return gamestatus::ERROR;
    }
  }
END: // end of game

  dealerDraw(btr,dealer_sum, dealer, _list, cardpos);

  // DEBUG
  cout<<"ME:";
  for (auto i : me)
    cout<<i<<" ";
  cout << "\n" << "Dealer:";
  for (auto i : dealer)
    cout<<i<<" ";
  cout<<"\n";
  // END DEBUG

  if(atr and me_sum+10 <= 21)
    me_sum+=10;

  return isWinLoseDraw(me_sum, dealer_sum);
}

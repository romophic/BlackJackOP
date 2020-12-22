#include "bjutil.cpp"
#include "blackjack.cpp"
#include <iostream>
#include <thread>
#include <cassert>
#include <mutex>
#include <deque>

using namespace std; 
long double getBetMoneyMG(int _gamestatus){
  switch (_gamestatus) {
  case gamestatus::WIN:
    return 2;

  case gamestatus::LOSE:
    return 0; 

  case gamestatus::DRAW:
    return 1;

  case gamestatus::DOUBLEDOWNTOWIN:
    return 4;

  case gamestatus::DOUBLEDOWNTOLOSE:
    return 0;

  case gamestatus::DOUBLEDOWNTODRAW:
    return 2;

  case gamestatus::SALENDER:
    return 0.5;

  case gamestatus::BLACKJACK:
    return 2.5;

  case gamestatus::ERROR:
    return -1;

  default:
    return -1;
  }
}

void upPos(int &_pos){
  _pos=min(3,_pos+1);
  return;
}
void downPos(int &_pos){
  _pos=max(0,_pos-1);
  return;
}

mutex mtx;
void f(vector<int> _bets,long double &_maxgetperbet,vector<int> &_maxarray){
  long double getmoney,betmoney;getmoney=betmoney=0;
  int pos=0;
  // a b c d
  // 0 1 2 3

  for(int i=0;i<100000;i++){ // 10^6
    betmoney+=_bets[pos];

    long double result = getBetMoneyMG(gameWithRandomList());
    if(result == -1){
      cout<<"something wrong\n";
      assert(false);
    }

    getmoney += _bets[pos]*result;
    if(1 < result){ // TODO: is that right?
      upPos(pos);
    }else{
      downPos(pos);
    }
  }

  if(getmoney / betmoney > _maxgetperbet){
    mtx.lock();
    _maxgetperbet = getmoney / betmoney;
    _maxarray=_bets;
    mtx.unlock();
  }
}

int main(){
  long double maxgetperbet=0;
  vector<int> maxarray(4,-1);
  vector<int> bets(4,0);

  deque<thread> tasks;

  cout<<"max thread: "<<thread::hardware_concurrency()<<"\n";
  cout<<"making tasks... "<<flush;
  for (bets[0] = 1; bets[0] <= 50; bets[0]++) {
    for (bets[1] = 1; bets[1] <= 50; bets[1]++) {
      cout<<bets[0]<<" "<<bets[1]<<" "<<bets[2]<<" "<<bets[3]<<"\n";
      for (bets[2] = 1; bets[2] <= 50; bets[2]++) {
        for (bets[3] = 1; bets[3] <= 50; bets[3]++) {
          tasks.emplace_front(thread(f,bets,ref(maxgetperbet),ref(maxarray)));
        }
      }
    for(auto &i:tasks){
      i.join();
    }
    tasks.clear();
    }
  }
  cout<<"complete\n";

  cout<<"wait tasks\n";
  for(auto &i:tasks){
    i.join();
  }

  for(auto i:maxarray){
    cout<<i<<" ";
  }
  cout<<"\n"<<maxgetperbet<<"\n";

}

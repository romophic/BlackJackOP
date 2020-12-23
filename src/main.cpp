#include "bjutil.cpp"
#include <iostream>
#include <thread>
#include <cassert>
#include <mutex>
#include <deque>

std::mt19937 mtforper{std::random_device{}()};
std::uniform_int_distribution<int> distforper(1, 10000000);
//10^7

namespace per{
  //sum = 1
  constexpr long double WIN    = 0.32531629;
  constexpr long double LOSE   = 0.41007484;
  constexpr long double DRAW   = 0.07719535;
  constexpr long double DDWIN  = 0.05256743;
  constexpr long double DDLOSE = 0.03678966;
  constexpr long double DDDRAW = 0.00662317;
  constexpr long double SLDR   = 0.04680537;
  constexpr long double BJ     = 0.04462789;
}

using namespace std; 
long double getBetMoneyMG(long double &_betmoney,const int _affectmoney){
  long double per = distforper(mtforper)/static_cast<long double>(10000000);

  using namespace per;

  if      (per <= (WIN)){ //WIN
    return 2;
  }else if(per <= (WIN)+(LOSE)){ //LOSE
    return 0;
  }else if(per <= (WIN)+(LOSE)+(DRAW)){ //DRAW
    return 1;
  }else if(per <= (WIN)+(LOSE)+(DRAW)+(DDWIN)){//DDWIN
    _betmoney+=_affectmoney;
    return 4;
  }else if(per <= (WIN)+(LOSE)+(DRAW)+(DDWIN)+(DDLOSE)){//DDLOSE
    _betmoney+=_affectmoney;
    return 0;
  }else if(per <= (WIN)+(LOSE)+(DRAW)+(DDWIN)+(DDLOSE)+(DDDRAW)){//DDDRAW
    _betmoney+=_affectmoney;
    return 2;
  }else if(per <= (WIN)+(LOSE)+(DRAW)+(DDWIN)+(DDLOSE)+(DDDRAW)+(SLDR)){//SLDR
    return 0.5;
  }else if(per <= (WIN)+(LOSE)+(DRAW)+(DDWIN)+(DDLOSE)+(DDDRAW)+(SLDR)+(BJ)){//BJ
    return 2.5;
  }

  return -1;
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

  for(int i=0;i<10000;i++){ // 10^5
    betmoney+=_bets[pos];

    long double result = getBetMoneyMG(betmoney,_bets[pos]);
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

void playGround(){
  vector<int> bets = {4,6,2,48};
  long double maxgetperbet=0;
  vector<int> maxarray(4,0);

  f(bets,maxgetperbet,maxarray);
  cout<<maxgetperbet<<"\n";
}

int main(){
  //playGround();
  /*
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
 */
}

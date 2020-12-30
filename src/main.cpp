// Need resultarray (in gameresult write by gamestatus::*)

#include "genresult_fromper.cpp"
#include "constvars.cpp"
#include "putlogo.cpp"
#include <iostream>
#include <ostream>
#include <thread>
#include <cassert>
#include <mutex>
#include <deque>
#include <fstream>
#include <iomanip>

using namespace std; 

void upPos(int &_pos){
  _pos=min(3,_pos+1);
}
void downPos(int &_pos){
  _pos=max(0,_pos-1);
}

mutex mtx_f;
void gameWithArray(vector<int> _bets,long double &_maxgetmoney,vector<int> &_maxarray){
  long double mymoney = handmoney;
  int pos=0;
  // a b c d
  // 0 1 2 3

  for(int i=0;i<gamelimit;i++){ // 10^5
    if(0 > mymoney)
      return;

    switch (resultarray[i]) {
    /*
     * (mymoney*_bets[pos]/100.0) means "How many bet"
     */
    case gamestatus::WIN:
      mymoney += (mymoney*_bets[pos]/100.0);
      upPos(pos);
      break;

    case gamestatus::LOSE:
      mymoney -= (mymoney*_bets[pos]/100.0);
      downPos(pos);
      break;

    case gamestatus::DRAW:
      break;

    case gamestatus::DOUBLEDOWNTOWIN:
      mymoney += (mymoney*_bets[pos]/100.0)*2;
      upPos(pos);
      break;

    case gamestatus::DOUBLEDOWNTOLOSE:
      mymoney -= (mymoney*_bets[pos]/100.0)*2;
      downPos(pos);
      break;

    case gamestatus::DOUBLEDOWNTODRAW:
      mymoney += (mymoney*_bets[pos]/100.0);
      break;

    case gamestatus::SALENDER:
      mymoney -= (mymoney*_bets[pos]/100.0)*0.5;
      downPos(pos);
      break;

    case gamestatus::BLACKJACK:
      mymoney += (mymoney*_bets[pos]/100.0)*1.5; //TODO:
      upPos(pos);
      break;

    case gamestatus::ERROR:
      assert(false);
      break;

    default:
      assert(false);
      break;
    }
  }

  if(mymoney > _maxgetmoney){
    mtx_f.lock();
    _maxgetmoney = mymoney;
    _maxarray=_bets;
    mtx_f.unlock();
  }

  return;
}

int main(){
  //fix format
  cout<<fixed<<setprecision(10);

  putLogo();

  cout<<"make results...\n";
  makeResult();
  cout<<"Done!\n";

  long double maxgetmoney=0;
  vector<int> maxarray(4,0); //write by persent(%) ex(100 -> 100%)
  vector<int> bets(4,0); // 2% ~ 100% between 2% 

  deque<thread> tasks; // for runnning solver

  cout<<"max thread: "<<thread::hardware_concurrency()<<"\n";
  cout<<"making tasks... \n";

  cout<<"configure:\n";
  cout<<"  gamelimit: \e[32m"<<gamelimit<<"\e[0m\n";
  cout<<"  handmoney: \e[32m"<<handmoney<<"\e[0m\n";

  for (bets[0] = 2; bets[0] <= 100; bets[0]+=2) {
    cout<<"\e[0G"<<"execute: \e[31m"<<(bets[0]-2)+((bets[1]-2)/50.0)<<"\e[0m%"<<" max value: \e[35m"<<maxgetmoney<<"\e[0m at \e[36m"
        <<"["<<maxarray[0]<<","<<maxarray[1]<<","<<maxarray[2]<<","<<maxarray[3]<<"]\e[0m"<<flush;

    for (bets[1] = 2; bets[1] <= 100; bets[1]+=2) {
      for (bets[2] = 2; bets[2] <= 100; bets[2]+=2) {
        for (bets[3] = 2; bets[3] <= 100; bets[3]+=2) {
          tasks.emplace_front(thread(gameWithArray,bets,ref(maxgetmoney),ref(maxarray)));
        }
      }

      for(auto &i:tasks)
        i.join();
      tasks.clear();
    }
  }

  cout<<"complete\n";

  cout<<"wait tasks\n";
  for(auto &i:tasks)
    i.join();

  cout<<"result:\n";
  for(auto i:maxarray)
    cout<<i<<" ";
  cout<<"\n"<<maxgetmoney<<"\n";

  cout<<"writting array...\n";
  ofstream of("array.csv");
  for(int i=0;i<resultarray.size()-1;i++)
    of<<resultarray[i]<<",";
  of<<resultarray[resultarray.size()-1];
  cout<<"All Done!!!\n";
}

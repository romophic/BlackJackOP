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
vector<int> nari(100000,0);
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
      mymoney += _bets[pos];
      upPos(pos);
      break;

    case gamestatus::LOSE:
      mymoney -= _bets[pos];
      downPos(pos);
      break;

    case gamestatus::DRAW:
      break;

    case gamestatus::DOUBLEDOWNTOWIN:
      mymoney += _bets[pos]*2;
      upPos(pos);
      break;

    case gamestatus::DOUBLEDOWNTOLOSE:
      mymoney -= _bets[pos]*2;
      downPos(pos);
      break;

    case gamestatus::DOUBLEDOWNTODRAW:
      break;

    case gamestatus::SALENDER:
      mymoney -= _bets[pos]*0.5;
      downPos(pos);
      break;

    case gamestatus::BLACKJACK:
      mymoney += _bets[pos]*1.5;
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

  nari[floor(mymoney)]++;

  return;
}

int main(){
  //fix format
  cout<<fixed<<setprecision(10);

  putLogo();

  long double maxgetmoney=0;
  vector<int> maxarray(4,0); //write by persent(%) ex(100 -> 100%)
  vector<vector<int>> bets = {
    {1,2,3,5},
    {1,3,2,6},
    {1,1,1,1},
    {10,10,10,10},
    {1,2,4,8},
    {2,4,6,10}
  };

  cout<<"Bets:\n";
  for(auto i:bets){
    cout<<"  ";
    for(auto j:i){
      cout<<j<<" ";
    }
    cout<<"\n";
  }

  ofstream resultfile("result.csv");

  for(auto &bet:bets){
    for(int c=0;c<10000;c++){
      makeResult();
      gameWithArray(bet,maxgetmoney,maxarray);
    }
    //clear nari
    for(int i=nari.size()-1;;i--){
      if(nari[i] == 0)
        nari.pop_back();
      else
        break;
    }

    for(auto i:nari){
      resultfile<<i<<",";
    }
    resultfile<<"\n";

    nari.clear();
    nari.resize(100000,0);
  }

}

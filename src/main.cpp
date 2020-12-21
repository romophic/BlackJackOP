#include "bjutil.cpp"
#include "blackjack.cpp"
#include <iostream>
#include <unordered_map>

using namespace std; 
long double getBetMoneyMG(int _gamestatus){
  switch (_gamestatus) {
  case gamestatus::WIN:
    return 2;

  case gamestatus::LOSE:
    return 0; 
  case gamestatus::DRAW:
    return 0.5;
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

int main(){
  auto upPos = [](int &_pos){
    _pos=min(3,_pos+1);
  };
  auto downPos = [](int &_pos){
    _pos=max(0,_pos-1);
  };

  vector<int> bets(4,0);

  long double maxgetperbet=0;
  vector<int> maxarray(4,-1);

  for (bets[0] = 1; bets[0] <= 50; bets[0]++) {
    for (bets[1] = 1; bets[1] <= 50; bets[1]++) {
      cout<<bets[0]<<" "<<bets[1]<<"\n";
      for (bets[2] = 1; bets[2] <= 50; bets[2]++) {
        for (bets[3] = 1; bets[3] <= 50; bets[3]++) {

          long double getmoney,betmoney;getmoney=betmoney=0;
          int pos=0;
          // a b c d
          // 0 1 2 3
          
          for(int i=0;i<2;i++){ // 10^6
            betmoney+=bets[pos];

            long double result = getBetMoneyMG(gameWithRandomList());
            if(result == -1){
              cout<<"something wrong\n";
              assert(false);
            }

            getmoney += bets[pos]*result;
            if(1 < result){ // TODO: is that right?
              upPos(pos);
            }else{
              downPos(pos);
            }
          }

          if(getmoney / betmoney > maxgetperbet){
            maxgetperbet = getmoney / betmoney;
            maxarray=bets;
          }

        }
      }
    }
  }

  for(auto i:maxarray){
    cout<<i<<" ";
  }
  cout<<"\n"<<maxgetperbet<<"\n";

}

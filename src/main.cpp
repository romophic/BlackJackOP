#include "bjutil.cpp"
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

double getBetMoneyMG(int _gamestatus){
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

constexpr long defaultmoney=10;

void updateBetMoney(long &_betmoney,int _gameresult){
  if(_gameresult == gamestatus::LOSE or _gameresult == gamestatus::DOUBLEDOWNTOLOSE or _gameresult == gamestatus::SALENDER){
    _betmoney = defaultmoney;
  }else{
    if(_betmoney == defaultmoney or _betmoney == defaultmoney*2){
      _betmoney *= 2;
    }else if(_betmoney == defaultmoney*4){
      _betmoney = defaultmoney*3;
    }
  }
}

void arrayGaming(void) {
  long betmoney=defaultmoney;
  long double paymoney=0;
  long double getmoney=0;

  cout.precision(10);

  for(int i=0;i<pow(10,6);i++){
    int gameresult=gameWithRandomList();

    paymoney+=betmoney;
    getmoney+=betmoney*getBetMoneyMG(gameresult);

    updateBetMoney(betmoney,gameresult);
  }
  cout<<paymoney<<" "<<getmoney<<"\n";
}

int main(){
  arrayGaming();
}

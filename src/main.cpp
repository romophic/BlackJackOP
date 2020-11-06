#include "util.cpp"
#include "blackjack.cpp"
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

void arrayGaming(void) {
  vector<int> list(15); // Initialcards

  boost::multiprecision::cpp_int money = 10;

  while(true){
    arrayFillRandom(list);
    fixArray(list);
    switch (game(list)) {
    case gamestatus::WIN:
      break;

    case gamestatus::LOSE:
      break;

    case gamestatus::DRAW:
      break;

    case gamestatus::DOUBLEDOWNTOWIN:
      break;

    case gamestatus::DOUBLEDOWNTOLOSE:
      break;

    case gamestatus::DOUBLEDOWNTODRAW:
      break;

    case gamestatus::SALENDER:
      break;

    case gamestatus::BLACKJACK:
      break;

    case gamestatus::ERROR:
      break;

    default:
      break;
    }
  }

  return;
}

int main(){
  arrayGaming();
}

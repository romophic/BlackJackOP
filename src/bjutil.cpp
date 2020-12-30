#pragma once

#include "blackjack.cpp"
#include <random>
#include <vector>
#include <iostream>

using namespace std;

void arrayFillRandom(vector<int> &_list) { // fill array random num (1 ~ 13)
  std::mt19937 mt{std::random_device{}()};
  std::uniform_int_distribution<int> dist(1, 13);
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

void fixArray(vector<int> &_list) {
  for (int &i : _list)
    if (10 <= i)
      i = 10;
}

int gameWithRandomList(){
  vector<int> list(15); // Initialcards
  arrayFillRandom(list);
  fixArray(list);
  return game(list);
}


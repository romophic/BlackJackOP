#pragma once

#include "bjutil.cpp"
#include "constvars.cpp"
#include <cassert>
#include <string>

using namespace std;

vector<int> resultarray;

namespace {
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

  int getGameStatusFromPer(){
    long double per = distforper(mtforper)/static_cast<long double>(10000000);

    using namespace per;

    if      (per <= (WIN)){ //WIN
      return gamestatus::WIN;
    }else if(per <= (WIN)+(LOSE)){ //LOSE
      return gamestatus::WIN;
    }else if(per <= (WIN)+(LOSE)+(DRAW)){ //DRAW
      return gamestatus::WIN;
    }else if(per <= (WIN)+(LOSE)+(DRAW)+(DDWIN)){//DDWIN
      return gamestatus::WIN;
    }else if(per <= (WIN)+(LOSE)+(DRAW)+(DDWIN)+(DDLOSE)){//DDLOSE
      return gamestatus::WIN;
    }else if(per <= (WIN)+(LOSE)+(DRAW)+(DDWIN)+(DDLOSE)+(DDDRAW)){//DDDRAW
      return gamestatus::WIN;
    }else if(per <= (WIN)+(LOSE)+(DRAW)+(DDWIN)+(DDLOSE)+(DDDRAW)+(SLDR)){//SLDR
      return gamestatus::WIN;
    }else if(per <= (WIN)+(LOSE)+(DRAW)+(DDWIN)+(DDLOSE)+(DDDRAW)+(SLDR)+(BJ)){//BJ
      return gamestatus::WIN;
    }

    assert(false);
    return gamestatus::ERROR;
  }
}//end of namespace

void makeResult(){ // result of gamelimit from bjutil
  for(int i=0;i<gamelimit;i++){
    resultarray.emplace_back(getGameStatusFromPer());
  }

  return;
}

#pragma once

#include "bjutil.cpp"
#include "constvars.cpp"
#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
#include <fstream>
#include <cassert>

using namespace std;

vector<int> resultarray;

namespace {
  mutex mtx_result;
  mutex mtx_persent;
  void threadGaming(int _n,int _threadnum) { // for multi threading
    int persent=0;
    for(int i=0;i<_n;i++){
      if(persent != int(double(i)/_n*100)){
        persent = int(double(i)/_n*100);
        mtx_persent.lock();
        cout<<_threadnum<<":"<<persent<<"%"<<endl;
        mtx_persent.unlock();
      }

      switch (gameWithRandomList()) {
      case gamestatus::WIN:
        mtx_result.lock();
        resultarray.push_back(gamestatus::WIN);
        mtx_result.unlock();
        break;

      case gamestatus::LOSE:
        mtx_result.lock();
        resultarray.push_back(gamestatus::LOSE);
        mtx_result.unlock();
        break;

      case gamestatus::DRAW:
        mtx_result.lock();
        resultarray.push_back(gamestatus::DRAW);
        mtx_result.unlock();
        break;

      case gamestatus::DOUBLEDOWNTOWIN:
        mtx_result.lock();
        resultarray.push_back(gamestatus::DOUBLEDOWNTOWIN);
        mtx_result.unlock();
        break;

      case gamestatus::DOUBLEDOWNTOLOSE:
        mtx_result.lock();
        resultarray.push_back(gamestatus::DOUBLEDOWNTOLOSE);
        mtx_result.unlock();
        break;

      case gamestatus::DOUBLEDOWNTODRAW:
        mtx_result.lock();
        resultarray.push_back(gamestatus::DOUBLEDOWNTODRAW);
        mtx_result.unlock();
        break;

      case gamestatus::SALENDER:
        mtx_result.lock();
        resultarray.push_back(gamestatus::SALENDER);
        mtx_result.unlock();
        break;

      case gamestatus::BLACKJACK:
        mtx_result.lock();
        resultarray.push_back(gamestatus::BLACKJACK);
        mtx_result.unlock();
        break;

      case gamestatus::ERROR:
        mtx_result.lock();
        resultarray.push_back(gamestatus::ERROR);
        mtx_result.unlock();
        assert(false);
        break;

      default:
        mtx_result.lock();
        resultarray.push_back(gamestatus::ERROR);
        mtx_result.unlock();
        assert(false);
        break;
      }
    }
  }
} //end of namespace

void makeResult(){ //result of gamelimit from bjutil
  int cores = thread::hardware_concurrency();
  resultarray.clear();

  vector<thread> tasks;
  
  for(int i=0;i<cores;i++)
    tasks.emplace_back(thread(threadGaming,gamelimit/cores,i));

  for(auto &i:tasks)
    i.join();

  return;
}

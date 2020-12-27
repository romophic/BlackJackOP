#include "bjutil.cpp"
#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
#include <fstream>
#include <cassert>

using namespace std;

vector<int> sumofresult(9, 0);
vector<int> resultarray;
mutex mtx_result;
mutex mtx_persent;

void threadGaming(int _n,int _threadnum) {
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
      sumofresult[0]++;
      resultarray.push_back(gamestatus::WIN);
      mtx_result.unlock();
      break;

    case gamestatus::LOSE:
      mtx_result.lock();
      sumofresult[1]++;
      resultarray.push_back(gamestatus::LOSE);
      mtx_result.unlock();
      break;

    case gamestatus::DRAW:
      mtx_result.lock();
      sumofresult[2]++;
      resultarray.push_back(gamestatus::DRAW);
      mtx_result.unlock();
      break;

    case gamestatus::DOUBLEDOWNTOWIN:
      mtx_result.lock();
      sumofresult[3]++;
      resultarray.push_back(gamestatus::DOUBLEDOWNTOWIN);
      mtx_result.unlock();
      break;

    case gamestatus::DOUBLEDOWNTOLOSE:
      mtx_result.lock();
      sumofresult[4]++;
      resultarray.push_back(gamestatus::DOUBLEDOWNTOLOSE);
      mtx_result.unlock();
      break;

    case gamestatus::DOUBLEDOWNTODRAW:
      mtx_result.lock();
      sumofresult[5]++;
      resultarray.push_back(gamestatus::DOUBLEDOWNTODRAW);
      mtx_result.unlock();
      break;

    case gamestatus::SALENDER:
      mtx_result.lock();
      sumofresult[6]++;
      resultarray.push_back(gamestatus::SALENDER);
      mtx_result.unlock();
      break;

    case gamestatus::BLACKJACK:
      mtx_result.lock();
      sumofresult[7]++;
      resultarray.push_back(gamestatus::BLACKJACK);
      mtx_result.unlock();
      break;

    case gamestatus::ERROR:
      mtx_result.lock();
      sumofresult[8]++;
      resultarray.push_back(gamestatus::ERROR);
      mtx_result.unlock();
      assert(false);
      break;

    default:
      mtx_result.lock();
      sumofresult[8]++;
      resultarray.push_back(gamestatus::ERROR);
      mtx_result.unlock();
      assert(false);
      break;
    }
  }
}

void makeResult(){ //result of 10^5
  int limit = pow(10,5);
  int cores = thread::hardware_concurrency();

  vector<thread> tasks;
  
  for(int i=0;i<cores;i++)
    tasks.emplace_back(thread(threadGaming,limit/cores,i));

  for(auto &i:tasks)
    i.join();
}

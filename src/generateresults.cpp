#include "bjutil.cpp"
#include <thread>
#include <vector>
#include <iostream>
#include <mutex>

using namespace std;

vector<int> result(9,0);
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
      result[0]++;
      mtx_result.unlock();
      break;

    case gamestatus::LOSE:
      mtx_result.lock();
      result[1]++;
      mtx_result.unlock();
      break;

    case gamestatus::DRAW:
      mtx_result.lock();
      result[2]++;
      mtx_result.unlock();
      break;

    case gamestatus::DOUBLEDOWNTOWIN:
      mtx_result.lock();
      result[3]++;
      mtx_result.unlock();
      break;

    case gamestatus::DOUBLEDOWNTOLOSE:
      mtx_result.lock();
      result[4]++;
      mtx_result.unlock();
      break;

    case gamestatus::DOUBLEDOWNTODRAW:
      mtx_result.lock();
      result[5]++;
      mtx_result.unlock();
      break;

    case gamestatus::SALENDER:
      mtx_result.lock();
      result[6]++;
      mtx_result.unlock();
      break;

    case gamestatus::BLACKJACK:
      mtx_result.lock();
      result[7]++;
      mtx_result.unlock();
      break;

    case gamestatus::ERROR:
      mtx_result.lock();
      result[8]++;
      mtx_result.unlock();
      break;

    default:
      mtx_result.lock();
      result[8]++;
      mtx_result.unlock();
      break;
    }
  }
}

int main(){
  int limit = pow(10,8);
  int cores = thread::hardware_concurrency();

  vector<thread> tasks;
  
  for(int i=0;i<cores;i++){
    tasks.emplace_back(thread(threadGaming,limit/cores,i));
  }

  for(auto &i:tasks){
    i.join();
  }

  for(int i:result){
    cout<<i<<" ";
  }
}

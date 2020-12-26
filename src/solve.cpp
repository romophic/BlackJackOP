#include "bjutil.cpp"
#include "blackjack.cpp"
#include "threadgame.cpp"
#include <thread>
#include <vector>

using namespace std;

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

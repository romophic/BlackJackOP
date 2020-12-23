#include "bjutil.cpp"
#include "blackjack.cpp"
#include "threadgame.cpp"
#include <thread>
#include <vector>

using namespace std;

int main(){
  int limit = pow(10,8);

  vector<thread> tasks;
  
  for(int i=0;i<4;i++){
    tasks.emplace_back(thread(threadGaming,int(limit/4),i));
  }

  for(auto &i:tasks){
    i.join();
  }

  for(int i:result){
    cout<<i<<" ";
  }
}

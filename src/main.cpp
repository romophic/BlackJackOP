/*
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

#define DEBUG

int getArrayMinNum(const vector<int> &_list) { // Returm most minimum num from
array vector<int> sums(_list.size(), 0); for (int i : _list) sums[i - 1]++;

  for (int i = 0; i < sums.size(); i++) {
    if (4 > sums[i]) { // 4 is max duplicate card nums
      return i+1;
    }
  }

  return -1;
}

bool isArrayCorrect(vector<int> &_list) {
  vector<int> sums(_list.size(), 0);
  for (int i : _list) {
    if (!(0 <= i and i <= 13))
      return false;
    sums[i - 1]++;
  }

  for (int i : sums)
    if (4 < i)
      return false;

  return true;
}

bool arrayUpdate(vector<int> &_list) { // Update array and return false if
can't(end) _list[_list.size()-1]++;

  vector<int> sums(13,0);
  for (int i = _list.size() - 1; i > 0; i--) { //kuriagari
    sums[_list[i]-1]++;
    if (13 < _list[i]) {
      _list[i]=getArrayMinNum(_list);
      _list[i-1]++;
    }
  }

  for (int i = _list.size() - 1; i > 0; i--) { //ataikaburi
    if (4 < sums[_list[i]-1]) {
      sums[_list[i] - 1]--;
      _list[i]++;
      sums[_list[i] - 1]++;
      if (13 < _list[i]) {
        _list[i]=getArrayMinNum(_list);
        sums[_list[i] - 1]++;
      }
    }
  }

  return true;
}

void game(vector<int> &_list) { // Excute GAME from array
#ifdef DEBUG
  for (int i : _list)
    cout << i << " ";
  cout << "\n";
#endif
}

int main(void) {
  vector<int> list = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4}; //Initial
cards

  int mem;
  for(int64_t i=0;;i++){
    arrayUpdate(list);
    if (isArrayCorrect(list)) {
    } else {
      cout<<"ERR\n";
      game(list);
      return 0;
    }
    if (mem != list[0]) {
      mem = list[0];
      game(list);
    }
  }
  cout<<"complete\n";
}

*/

#include <exception>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;
void do_worker1() {
  for (int i = 0; i < 5; i++) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
void do_worker2() {
  for (int i = 0; i < 5; i++) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}

int main(int argc, char *argv[]) {
  try {
    std::thread t1(do_worker1);
    std::thread t2(do_worker2);
    t1.join();
    t2.join();
  } catch (std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
  return (0);
}
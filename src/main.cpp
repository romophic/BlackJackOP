#include "blackjack.cpp"

//generate random num
std::mt19937 mt{std::random_device{}()};
std::uniform_int_distribution<int> dist(1, 13);

void putArrayNums(const vector<int> &_list, const string _str) { // put array
  cout << _str << ": ";
  for (int i : _list)
    cout << i << " ";
  cout << "\n";
}

void arrayFillRandom(vector<int> &_list) { // fill array random num (1 ~ 13)
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

vector<int> result(8,0);
mutex mtx_result;
mutex mtx_persent;

void threadGaming(int _n,int _threadnum) {
  vector<int> list(15,0); // Initialcards
  int persent=0;
  for(int i=0;i<_n;i++){
    if(persent != int(double(i)/_n*100)){
      persent = int(double(i)/_n*100);
      mtx_persent.lock();
      cout<<_threadnum<<":"<<persent<<"%"<<endl;
      mtx_persent.unlock();
    }
    arrayFillRandom(list);
    fixArray(list);

    switch (game(list)) {
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

int main(void) {
  putLogo();

  long n;
  int threadnum=thread::hardware_concurrency();
  vector<int> list(15,0); // Initialcards
  ofstream resultfile("result.csv");
  if (!resultfile.is_open()) {
    cout<<"File open error\n";
    return -1;
  }

  cout<<"How many test?(x"<<threadnum<<") :"<<flush;
  cin>>n;

  vector<thread> threads;

  cout<<"Making threads...\n";
  for (int i=0;i<threadnum;i++){
    threads.emplace_back(thread(threadGaming,n,i));
    cout<<i+1<<"/"<<threadnum<<"\n";
  }
  cout<<"done!\n";

  cout<<"Waiting threads...  \n";
  for (int i=0;i<threadnum;i++){
    threads[i].join();
    cout<<i<<":👍"<<"\n";
  }
  cout<<"Complete excuting!\n";

  resultfile << "SUM," << n*threadnum << "\n";
  resultfile << "WIN," << result[0] << "\n";
  resultfile << "LOSE," << result[1] << "\n";
  resultfile << "DRAW," << result[2] << "\n";
  resultfile << "DOUBLEDOWNTOWIN," << result[3] << "\n";
  resultfile << "DOUBLEDOWNTOLOSE," << result[4] << "\n";
  resultfile << "DOUBLEDOWNTODRAW," << result[5] << "\n";
  resultfile << "SALENDER," << result[6] << "\n";
  resultfile << "BLACKJACK," << result[7] << "\n";
  resultfile << "ERROR," << result[8];
}

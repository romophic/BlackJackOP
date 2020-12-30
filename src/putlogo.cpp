#include<iostream>
#include<vector>
#include<string>
void putLogo(){
  using namespace std;

  vector<string> logo = {
#include "logo.txt"
  };

  for(auto &i:logo){
    cout<<i<<"\n";
  }
}

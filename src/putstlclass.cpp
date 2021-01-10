#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <tuple>
#include <map>
#include <set>

using namespace std;

template <typename T>
ostream &operator<<(ostream &_ostr, const vector<T> &_v);
template <typename T>
ostream &operator<<(ostream &_ostr, const deque<T> &_v);
template <typename T>
ostream &operator<<(ostream &_ostr, const list<T> &_v);
template <typename T, typename Y>
ostream &operator<<(ostream &_ostr, const pair<T, Y> &_v);
template <class... Ts>
ostream &operator<<(ostream &_ostr, const tuple<Ts...> &t);
template <typename T, typename Y>
ostream &operator<<(ostream &_ostr, const map<T, Y> &_v);
template <typename T>
ostream &operator<<(ostream &_ostr, const set<T> &_v);

template <typename T>
ostream &operator<<(ostream &_ostr, const vector<T> &_v) {
  _ostr << "v";
  if (_v.empty()) {
    _ostr << "{ }";
    return _ostr;
  }
  _ostr << "{" << *_v.begin();
  for (auto itr = ++_v.begin(); itr != _v.end(); itr++) {
    _ostr << ", " << *itr;
  }
  _ostr << "}";
  return _ostr;
}
template <typename T>
ostream &operator<<(ostream &_ostr, const deque<T> &_v) {
  _ostr << "d";
  if (_v.empty()) {
    _ostr << "{ }";
    return _ostr;
  }
  _ostr << "{" << *_v.begin();
  for (auto itr = ++_v.begin(); itr != _v.end(); itr++) {
    _ostr << ", " << *itr;
  }
  _ostr << "}";
  return _ostr;
}
template <typename T>
ostream &operator<<(ostream &_ostr, const list<T> &_v) {
  _ostr << "l";
  if (_v.empty()) {
    _ostr << "{ }";
    return _ostr;
  }
  _ostr << "{" << *_v.begin();
  for (auto itr = ++_v.begin(); itr != _v.end(); itr++) {
    _ostr << ", " << *itr;
  }
  _ostr << "}";
  return _ostr;
}
template <typename T, typename Y>
ostream &operator<<(ostream &_ostr, const pair<T, Y> &_v) {
  _ostr << "p(" << _v.first << ", " << _v.second << ")";
  return _ostr;
}
template <class... Ts>
ostream &operator<<(ostream &_ostr, const tuple<Ts...> &_v) {
  _ostr << "t[";
  bool first = true;
  apply([&_ostr, &first](auto &&... args) {
    auto print = [&](auto &&val) {
      if (!first)
        _ostr << ",";
      (_ostr << val);
      first = false;
    };
    (print(args), ...);
  },
        _v);
  _ostr << "]";
  return _ostr;
}
template <typename T, typename Y>
ostream &operator<<(ostream &_ostr, const map<T, Y> &_v) {
  _ostr << "m{";
  for (auto itr = _v.begin(); itr != _v.end(); itr++) {
    _ostr << "(" << itr->first << ", " << itr->second << ")";
    itr++;
    if (itr != _v.end())
      _ostr << ", ";
    itr--;
  }
  _ostr << "}";
  return _ostr;
}
template <typename T>
ostream &operator<<(ostream &_ostr, const set<T> &_v) {
  _ostr << "s{";
  for (auto itr = _v.begin(); itr != _v.end(); itr++) {
    _ostr << *itr;
    ++itr;
    if (itr != _v.end())
      _ostr << ", ";
    itr--;
  }
  _ostr << "}";
  return _ostr;
}

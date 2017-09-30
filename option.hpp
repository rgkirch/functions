#pragma once

template <typename T>
class Option {
  Option(T t) : (t), valid(true) {}
  Option() : valid(false) {}
  bool() {
    return valid;
  }
  virtual ~Option() {};
private:
  T t;
  bool valid;
};

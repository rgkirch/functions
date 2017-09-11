#include <string>
#include <vector>

using namespace std;

template <typename T>
struct For;

template <typename F>
struct Callable {
  Callable(F f) : f(f) {}
  F f;
};

struct Any {
  template <typename T>
  Any(T t) : model(new Model<T>(t)) {}

  template <typename T>
  auto get()->optional<T> {
    auto thing = dynamic_cast<Model<T>*>(model);
    if(thing != nullptr) {
      return f(thing->data);
    } else {
      return {};
    }
  }
  struct Concept {
    virtual ~Concept() = default;
  };
  template <typename T>
  struct Model : public Concept {
    Model(T t) : data(t) {}
    T data;
  };

  Concept *model;
};

struct ForConcept {
  ForConcept() : next(nullptr) {
  }
  template <typename T>
  For<T>& operator()(T t) {
    auto f = new For<T>(t);
    push_back(f);
  }
  void push_back(ForConcept *f) {
    if(next == nullptr) {
      next = f;
    } else {
      next->push_back(f);
    }
  }
  template <typename F>
  auto apply(F f) {
    fun = f;
  }
  Any fun;
  virtual ~ForConcept() = default;
  ForConcept *next;
};

template <typename T>
struct For : public ForConcept, public forward_iterator_tag {
  For(T t) : value(t) {}
  T value;
};

int main() {
  For<vector<int>>(
    vector<int>{1, 2, 3}
  )(
    vector<char>{'a', 'b', 'c'}
  ).apply([=](int i, char c){
      if(i + c == 'd') return true;
      else return false;
    });
}

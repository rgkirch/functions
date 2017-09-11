#include <string>
#include <experimental/optional>
#include <vector>

using namespace std;
using namespace std::experimental;

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
  auto& operator()(T t) {
    auto f = new For<T>(t);
    push_back(f);
    return *this;
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
    //fun = f;
    fc = new FunctionModel<F>(f);
  }
  //Any fun;
  struct FunctionConcept {
    virtual ~FunctionConcept() = default;
  };
  template <typename T>
  struct FunctionModel : public FunctionConcept {
    FunctionModel(T t) : f(t) {}
    template <typename... Args>
    auto operator()(Args... args) {
      return f(args...);
    }
    T f;
  };
  FunctionConcept *fc;

  virtual ~ForConcept() = default;
  ForConcept *next;
};

template <typename T>
struct For : public ForConcept {
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

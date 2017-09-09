#include <vector>
#include <memory>
#include <string>
#include <functional>
#include <iostream>


// Default print; stream to cout:
template <typename T>
void print(T const& t){ std::cout << t <<"\n"; }

// Functional-style loops:
struct Object;
using Body=std::function<void(Object)>;
using Loop=std::function<void(Body)>;

// default foreach: return a loop that just visits yourself:
template <typename T>
Loop foreach(T const& t) {
    return [t](Body body){ body(t); };
}

// custom printing:
inline void print(std::string const& str) {
    std::cout << "\"" << str  <<"\"" << std::endl;
}
inline void print(int i) {
    std::cout << "Integer: "<< i << std::endl;
}
// such custom prints can go here, or in the namespace of the type.

// Objects are actually smart pointers to type-erased data:
struct Object {
    template <typename T>
    Object(T t) : model(std::make_shared<Model<T>>(std::forward<T>(t))) {
        //  std::cout << "construct object from T" << std::endl;
    }

    friend void print(Object o){
        o.model->do_print();
    }
    friend Loop foreach(Object o){
        return o.model->do_foreach();
    }
    struct Concept {
        virtual void do_print() =0;
        virtual Loop do_foreach() = 0;
        // no dtor, as shared ptr handles that
    };

    template <typename T>
    struct Model final : Concept {
        Model(T t) : data(std::forward<T>(t)) {}
        void do_print() override {
            print(data);
        }
        Loop do_foreach( ) override {
            return foreach(data);
        }
        T data;
    };
    std::shared_ptr<Concept> model;
};


struct For {
    For() {}
    template<class...Ts>
    For(Ts const&...ts):
            objects({ts...})
    {}
    // given an Object o, return that object's contents
    // in a For.
    static For box(Object o) {
        For tmp;
        foreach(o)([&tmp](Object o){ tmp+=o; });
        return tmp;
    }
    For(For const&)=default;
    For& operator+=(Object o){ objects.push_back(o); return *this; }
    For operator+(Object o) const { For tmp=*this; tmp+= o; return tmp; }
    For operator*(For rhs)const{
        For tmp;
        for( auto o1 : objects )
            for( auto o2 : rhs.objects )
            {
                tmp += box(o1) + o2;
            }
        return tmp;
    }
    For& operator*=(For rhs){
        *this = *this*rhs;
    }
    template<class...Ts>
    For operator()(Ts const&... ts) {
        *this *= For(ts...);
        return *this;
    }
    friend Loop foreach(For const& f){
        return [f](Body body){
            for(auto o : f.objects) {
                body(o);
            }
        };
    }

    friend void print(For f) {
        std::cout << "{";
        for(auto o : f.objects) {
            print(o);
        }
        std::cout << "}\n";
    };
    std::vector<Object> objects;
};

int main() {
    auto a = For(std::string("hello"),42)(1,-1);
    auto b = a;
    b('a','b','c');
    std::cout <<"a:\n";
    print(a);
    std::cout <<"b:\n";
    print(b);
}

#pragma once

class Option {
    virtual ~Option() =0;
};

template <typename T>
class Some : public Option {
public:
    Some(T t) : (t) {}
    operator bool() {
        return true;
    }
private:
    T t;
};

class None : public Option {
    operator bool() {
        return false;
    }
};

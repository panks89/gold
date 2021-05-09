#include <iostream>

/* static interface using CRTP */

template<typename T, template<typename> class crtpType>
class crtp {
    crtp() {}
    friend crtpType<T>;
public:
    T& underlying() { return static_cast<T&>(*this); }
    const T& underlying() const { return static_cast<const T&>(*this); }
};

template<typename T>
class doubler : public crtp<T, doubler> {
public:
    using CRTP = doubler;
    void doubleIt() {
        this->underlying().setValue(2 * this->underlying().getValue());
    }
};

template<typename T>
class half : public crtp<T, half> {
public:
    void halfIt() {
        this->underlying().setValue(this->underlying().getValue()/2);
    }
};


class data : public half<data>, private doubler<data> {
    int value;
public:
    friend CRTP;
    /* Getter and Setter */
    const int& getValue() { return value; }
    void setValue(int v) { value = v; }
};

int main() {
    data d;
    d.setValue(10);
    std::cout << " Current data value : " << d.getValue() << std::endl;
    d.doubleIt();
    std::cout << " New data value : " << d.getValue() << std::endl;
    d.halfIt();
    std::cout << " New data value : " << d.getValue() << std::endl;
}

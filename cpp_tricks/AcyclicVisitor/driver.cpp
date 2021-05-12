#include <iostream>
#include "visitor.h"

using namespace std;

struct A : visitableBase { DEFINE_VISITABLE(); };

struct B : A { DEFINE_VISITABLE(); };

struct C : B { DEFINE_VISITABLE(); };

struct D : A { DEFINE_VISITABLE(); };

struct abcdVisitor : visitorBase, visitor<A>, visitor<B>, visitor<C>, visitor<D> {

    void visit(A & a) override {
        cout << "In A visited!!!\n";
    }

    void visit(B & b) override {
        cout << "In B visited!!!\n";
    }

    void visit(C & c) override {
        cout << "In C visited!!!\n";
    }

    void visit(D & d) override {
        cout << "In D visited!!!\n";
    }
};

int main() {
    abcdVisitor v;
    A *a = new A();
    A *ab = new B();
    A *ad = new D();
    A an = *ad;
    a->accept(v);
    ad->accept(v);
}

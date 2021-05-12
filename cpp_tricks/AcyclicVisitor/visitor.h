#ifndef VISITOR_H
#define VISITOR_H

struct visitorBase {
    virtual ~visitorBase() = default;
};

template <typename T>
struct visitor {
    virtual void visit(T &) = 0;
};


struct visitableBase {
    virtual void accept(visitorBase &) = 0;
};

struct visitableImpl {
    template <typename T>
    static void acceptImpl(T &visitable, visitorBase &vb) {
        visitor<T>* v = dynamic_cast<visitor<T>*>(&vb);
        if (v) { v->visit(visitable); }
    }
};

#define DEFINE_VISITABLE() \
    void accept(visitorBase &vb) override { \
    visitableImpl::acceptImpl(*this, vb); \
    }

#endif /* VISITOR_H */

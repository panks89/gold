#ifndef MAYBE_H
#define MAYBE_H

template<typename Object>
struct Maybe {
    Object *object;
    Maybe(Object *object) : object { object } { }

    template <typename Functor>
    auto with(Functor &&func) {
        return object ? maybe(func(object)) : nullptr;
    }

    template <typename Functor>
    auto execute(Functor &&func) {
        if (object) { func(object); }
        return *this;
    }

};

template <typename Object>
auto maybe(Object *object) {
    return Maybe<Object> {object};
}

#endif /* MAYBE_H */

#ifndef ITERATOR_H
#define ITERATOR_H

template<typename T, typename R>
struct Iterator {

    std::coroutine_handle<T> m_coroutine {nullptr};

    Iterator() = default;
    
    Iterator(std::coroutine_handle<T> coroutine) : m_coroutine {coroutine} { }

    void operator++() {
        m_coroutine.resume();
    }
    
    const R& operator*() const {
        return *(m_coroutine.promise().current_value);
    }
    
    bool operator==(std::default_sentinel_t) const {
        return !m_coroutine || m_coroutine.done();
    }
};

#endif /* ITERATOR_H */

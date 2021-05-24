#ifndef GENERATOR_H
#define GENERATOR_H

#include <coroutine>
#include <optional>
#include "Iterator.h"

template <typename T, typename R>
struct PromiseType {

    R get_return_object() {
        return R {this};
    }
        
    std::suspend_always initial_suspend() noexcept {
        return {};
    }

    std::suspend_always final_suspend() noexcept {
        return {};
    }
        
    std::suspend_always yield_value(T value) noexcept {
        current_value = std::move(value);
        return {};
    }
        
    // Disallow co_await in generator coroutines.
    void await_transform() = delete;

    [[noreturn]] void unhandled_exception() {
        throw;
    }

    std::optional<T> current_value;
};


template<std::movable T>
class Generator {
public:
    using promise_type = PromiseType<T, Generator>;

    using Handle = std::coroutine_handle<promise_type>;

    using iterator = Iterator<promise_type, T>;

    iterator begin() {
        if (m_coroutine) {
            m_coroutine.resume();
        }
        return iterator {m_coroutine};
    }

    std::default_sentinel_t end() {
        return {};
    }

    explicit Generator(promise_type * p) : m_coroutine {Handle::from_promise(*p)} { }

    Generator() = default;

    ~Generator() {
        if (m_coroutine) {
            m_coroutine.destroy();
        }
    }

    Generator(const Generator&) = delete;
    
    Generator& operator=(const Generator&) = delete;

    Generator(Generator&& other) noexcept : m_coroutine {other.m_coroutine} {
        other.m_coroutine = {};
    }
    
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (m_coroutine) {
                m_coroutine.destroy();
            }
            m_coroutine = other.m_coroutine;
            other.m_coroutine = {};
        }
        return *this;
    }
    
protected:
    Handle m_coroutine;
};

#endif /* GENERATOR_H */

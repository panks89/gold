#include <coroutine>
#include <type_traits>
#include <future>
#include <iostream>

template<typename T, typename... Args>
requires(!std::is_void_v<T> && !std::is_reference_v<T>)
struct std::coroutine_traits<std::future<T>, Args...> {
    struct promise_type {
        std::future<T> get_return_object() noexcept {
            std::cout << "get_return_object\n";
            return p.get_future();
        }

        std::suspend_never initial_suspend() const noexcept {
            std::cout << "Initial Suspend\n";
            return {};
        }

        std::suspend_never final_suspend() const noexcept {
            std::cout << "Final Suspend\n";
            return {};
        }

        void return_value(const T& value) noexcept(std::is_nothrow_copy_constructible_v<T>) {
            std::cout << " return_value" << "\n";
            p.set_value(value);
        }

        void return_value(T&& value) noexcept(std::is_nothrow_move_constructible_v<T>) {
            std::cout << " return_value" << "\n";
            p.set_value(std::move(value));
        }

        void unhandled_exception() noexcept {
            p.set_exception(std::current_exception());
        }

    private:
        std::promise<T> p;
    };
};

std::future<int> make_future() {
    std::cout << " Hello :\n";
    co_return 42;
}    

int main () {
    auto fut { make_future() };
    std::cout << "Read out future value : ";
    std::cout << fut.get() << std::endl;
}

/*
  g++-10 -g -std=c++2a -fcoroutines -pthread Future.cpp
  Output:
  get_return_object
  Initial Suspend
   Hello :
   return_value
  Final Suspend
  Read out future value : 42
*/

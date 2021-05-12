#include <iostream>
#include <thread>
#include <chrono>
#include "shared_ptr.h"

struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    virtual ~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};

void thr(local::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    local::shared_ptr<Base> lp = p; // thread-safe, even though the
    // shared use_count is incremented
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread:\n"
                  << "  lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}

int main()
{
    std::cout << "Hello World!\n";

    std::cout << "Test1 :" << std::endl;
    local::shared_ptr<Base> p {new Derived()};

    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    std::thread t1(thr, p), t2(thr, p), t3(thr, p);
    p.reset(); // release ownership from main
    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    t1.join(); t2.join(); t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";

    std::cout << "Test2 :" << std::endl;

    local::shared_ptr<int> sptr{ new int(10) };
    {
        local::shared_ptr<int> sptr_copy{ sptr };
        local::shared_ptr<int> ptr{ new int(20) };
        local::shared_ptr<int> ptr1{ ptr };
        std::cout << " sptr_copy use_count = " << sptr_copy.use_count() << std::endl; // 2
        sptr = std::move(ptr);
        std::cout << *ptr1 << std::endl;
        std::cout << " sptr_copy use_count = " << sptr_copy.use_count() << std::endl; // 1
        std::cout << " sptr_copy : " << *sptr_copy << std::endl; // 10
        std::cout << " sptr use_count = " << sptr.use_count() << std::endl; // 2
    }
    std::cout << " sptr : " << *sptr << std::endl; // 20
    std::cout << " sptr use_count = " << sptr.use_count() << std::endl; // 1
}

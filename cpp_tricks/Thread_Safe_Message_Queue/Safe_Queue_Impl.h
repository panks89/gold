#include "Safe_Queue.h"
#include <iostream>

template<typename T>
void Safe_Queue<T>::put(const T& val)
{
  std::unique_ptr<Message<T>> uptr = std::make_unique<Message<T>>(val);
  std::lock_guard<std::mutex> lock(mtx); // lock_guard can lock only once
  q.push(std::move(uptr));
  cond.notify_one();
} // implicitly unlocked the mutex on destruction

template<typename T>
std::unique_ptr<Message<T>> Safe_Queue<T>::get()
{
  std::unique_lock<std::mutex> lock(mtx);
  std::cout << "thread would sleep if not element to get()" << std::endl;
  cond.wait(lock, [this]{ return !q.empty(); });
  std::cout << "thread active" << std::endl;
  std::unique_ptr<Message<T>> uptr = std::move(q.front());
  q.pop();
  return uptr;
}

template<typename T>
void Safe_Queue<T>::put(T&& val)
{
  std::unique_ptr<Message<T>> uptr =
    std::make_unique<Message<T>>(std::move(val));
  std::lock_guard<std::mutex> lock(mtx); // lock_guard can lock only once
  q.push(std::move(uptr));
  cond.notify_one();
}


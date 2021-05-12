#pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "Message.h"

/*
 * put() and get() will not get in each others way.
 * A thread that does a get() will sleep unless there 
 * is a value on the queue for it to get.
 */

template<typename T>
class Safe_Queue
{
  std::mutex mtx;
  std::condition_variable cond;
  std::queue<std::unique_ptr<Message<T>>> q;
 public:
  void put(const T& val);
  void put(T&& val);
  std::unique_ptr<Message<T>> get();
};

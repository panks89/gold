#ifndef INTERRUPTIBLE_THREAD_H
#define INTERRUPTIBLE_THREAD_H

#include <thread>
#include <atomic>

class threadInterrupted { };

class InterruptFlag {
  std::atomic<bool> flag;
public:
  void set() { flag.store(true, std::memory_order_relaxed); }
  bool isSet() const {
    return flag.load(std::memory_order_relaxed);
  }
};

thread_local InterruptFlag threadLocalFlag;
void interruptionPoint() {
  if (threadLocalFlag.isSet()) {
    throw threadInterrupted();
  }
}

class InterruptibleThread {
  std::thread internalThread;
  InterruptFlag *flag;
public:
  template<typename Callable>
  InterruptibleThread(Callable F) {
    std::promise<InterruptFlag*> p;
    internalThread = std::thread([F, &p](){
	p.set_value(&threadLocalFlag);
	try {
	  F();
	} catch(const threadInterrupted &e) {
	  // Thread Over
	  std::cout << "Thread is interrupted.\n";
	}
      });
    flag = p.get_future().get();
  }

  bool joinable() const { return internalThread.joinable(); }
  void interrupt() {
    flag->set();
  }
  void join() { internalThread.join(); }
  
};

#endif /* INTERRUPTIBLE_THREAD_H */


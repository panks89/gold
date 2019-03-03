#include "Safe_Queue.h"
#include "Safe_Queue_Impl.h"
#include <iostream>

Safe_Queue<int> sq;

void producer()
{
  int x;
  while(std::cin >> x)
    {
      sq.put(x);
    }
  std::cout << "producer dies!!!\n";
}

void consumer()
{
  while(true)
    {
      std::unique_ptr<Message<int>> uptr = sq.get();
      std::cout << uptr->getData() << " is consumed!!!!" << std::endl;
    }
}

int main()
{
  std::thread t1(consumer); t1.detach();
  std::thread t2(producer);
  t2.join();
}

#include <iostream>
#include <string>
#include <future>
#include <chrono>
#include "Interruptible_Thread.h"

using namespace std;

string getUserInput() {
  string input;
  std::cout << "Waiting for user input:\n";
  getline(cin, input);
  return input;
}

void DoBlockGetLine() {  
  while(true) {
    interruptionPoint();
    std::packaged_task<std::string()> task(getUserInput);
    std::future<string> future = task.get_future();
    std::thread t(std::move(task)); t.detach();
    while (!threadLocalFlag.isSet()) {
      if (future.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
	const string input { future.get() };
	std::cout << "# " << input << std::endl;
	break;
      }
      interruptionPoint();
    }
  }
}

int main()
{
  InterruptibleThread t {DoBlockGetLine};
  /* Sleep for 10 seconds; Do some heavy work */
  this_thread::sleep_for(std::chrono::seconds(10));
  t.interrupt();
  if (t.joinable()) { t.join(); }
}

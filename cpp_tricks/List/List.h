#ifndef LIST_H
#define LIST_H

#include <memory>
#include "Node.h"
#include "NodeIterator.h"
#include "debug.h"

namespace gold {

  template <typename T> class List;

  template <typename T>
  inline std::ostream& operator<<(std::ostream &os, List<T> &lst) {
    NodeIterator<T> itr{lst.begin()}, end;
    while (itr != end) {
      os << *itr;
      ++itr;
    }
    os << std::endl;
    return os;    
  }
  
  template <typename T>
  class List {
    using nodeObj = Node<T>;
    using nPtr = std::unique_ptr<nodeObj>;
    nPtr header;
    /* Speed up push_back */
    nodeObj *last; 
  public:
    using iterator = NodeIterator<T>;
    explicit List() = default;
    explicit List(std::initializer_list<T> il) {
      for (auto i : il) { this->push_back(i); } 
    }
    ~List() {
      DEBUG_MSG("Destructor called on List. . .");
    }
    void push_back(const T &value) {
      if (last) {
	last->next = std::make_unique<nodeObj>(value);
	last = last->next.get();
      } else {
	header = std::make_unique<nodeObj>(value);
	last = header.get();
      }
    }
    
    void push_front(const T &value) {
      nPtr newHeader = std::make_unique<nodeObj>(value);
      newHeader->next.reset(header.release());
      header.reset(newHeader.release());
    }

    iterator begin() {
      return {header.get()};
    }

    iterator end() {
      return {nullptr};
    }
    
    friend std::ostream& operator<< <>(std::ostream &os, List &);
  };
}

#endif /* LIST_H */

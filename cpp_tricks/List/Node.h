#ifndef NODE_H
#define NODE_H

#include <memory>
#include <iostream>
#include <sstream>
#include "debug.h"

namespace gold {
  /* Forward Declaration*/
  template <typename T> class List;
  template <typename T> class NodeIterator;
  template <typename T> class Node;
  
  template <typename T>
  inline std::ostream& operator<<(std::ostream &os, const Node<T> &node) {
    os << node.data << " ";
    return os;    
  }

  template <typename T>
  class Node {
    T data;
    /*
     * unique_ptr would prevent compiler 
     * to create synthesized copy ctors.
     */
    std::unique_ptr<Node> next;
  public:
    Node(const T &value) : data(value)  { }
    ~Node() {
#ifdef DEBUG
      std::ostringstream ss(std::ostringstream::ate);
      ss<<"dtor on Node: " << *this;
      DEBUG_MSG(ss.str());
#endif
      for (auto current = std::move(next);
	   current ;
	   current = std::move(current->next));
    }
    void swap(Node &other) {
      using std::swap;
      swap(data, other.data);
    }
    friend class List<T>;
    friend class NodeIterator<T>;
    friend std::ostream& operator<< <>(std::ostream &os, const Node &);
  };
  template<typename T>
  void swap(Node<T>& first, Node<T>& second) {
    first.swap(second);
  }
}

#endif /* NODE_H */

#ifndef NODEITERATOR_H
#define NODEITERATOR_H

#include <iterator>
#include "Node.h"
namespace gold {
  template <typename T>
  class NodeIterator :
    public std::iterator<std::forward_iterator_tag, Node<T>> {
  public:
    using super = std::iterator<std::forward_iterator_tag, Node<T>>;
    using pointer = typename super::pointer;
    using reference = typename super::reference;
    using value_type = typename super::value_type;
    using difference_type = typename super::difference_type;
  private:
    pointer node;
  public:
    NodeIterator() : node(nullptr) { }
    NodeIterator(pointer ptr) : node(ptr) { }
    NodeIterator(const reference node) { this->node = &node; }
    NodeIterator(const NodeIterator& itr) { node = itr.node; }
    NodeIterator& operator++() {
      /* Pre Increment */
      node = node->next.get();
      return *this;
    }
    NodeIterator operator++(int) {
      /* Post Increment */
      NodeIterator tmp(*this);
      operator++();
      return tmp;
    }
    reference operator*() {
      return *node;
    }
    pointer operator->() {
      return node;
    }
    bool operator==(const NodeIterator& rhs) const {
      return node == rhs.node;
    }
    bool operator!=(const NodeIterator& rhs) const {
      return node != rhs.node;
    }
    void swap(NodeIterator& other) {
      using std::swap;
      swap(node->data, other.node->data);
    }
  };

  template<typename T>
  void swap(NodeIterator<T>& first, NodeIterator<T>& second) {
    first.swap(second);
  }
}

#endif /* NODEITERATOR_H */

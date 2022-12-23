#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;

  void Copy(const CircularLinkedList<T>& source);
  void Clear();
  void InsertAsc(const T& data);
  void InsertDesc(const T&data);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  Copy(source);
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
  if (&source == this) {
    return *this;
  }
  Clear();
  Copy(source);
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  Clear();
}


template <typename T>
void CircularLinkedList<T>::Copy(const CircularLinkedList<T>& source) {
  if (source.head_ != nullptr) {
    node_order_ = source.node_order_;
    head_ = new Node(source.head_.data);
    Node<T>* source_curr = source.head_;
    Node<T>* this_curr = head_;
    while (source_curr != source.tail_) {
      this_curr->next = new Node(source_curr->next.data);
      this_curr = this_curr->next;
      source_curr = source_curr->next;
    }
    this_curr->next = head_;
    tail_ = this_curr;

    source_curr = nullptr;
    this_curr = nullptr;
  }
}

template <typename T>
void CircularLinkedList<T>::Clear() {
  if (head_ != nullptr) {
    tail_->next = nullptr;
    tail_ = nullptr;
    while (head_) {
      Node<T>* next = head_->next;
      delete head_;
      head_ = next;
    }
  }
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    head_ = Node(data);
    head_->next = head_;
    tail_ = head_;
  }
  if (node_order_ == Order::kASC) {
    InsertAsc(data);
  } else {
    InsertDesc(data);
  }
}

template <typename T>
void CircularLinkedList<T>::InsertAsc(const T& data) {
  bool inserted = false;
  Node<T>* prev = head_;
  Node<T*> curr = head_->next;
  if (data < head_->data) {
    tail_->next = Node(data, head_);
    head_ = tail_->next;
    inserted = true;
  } else {
    while (prev != tail_) {
      if (data >= prev->data && data < curr->data && !inserted) {
        prev->next = Node(data, curr);
        inserted = true;
      }
      prev = prev->next;
      curr = curr->next;
    }
  }
  if (!inserted) {
    prev->next = Node(data, curr);
    tail_ = prev->next;
  }
  prev = nullptr;
  curr = nullptr;
}

template <typename T>
void CircularLinkedList<T>::InsertDesc(const T&data) {
  bool inserted = false;
  Node<T>* prev = head_;
  Node<T*> curr = head_->next;
  if (data > head_->data) {
    tail_->next = Node(data, head_);
    head_ = tail_->next;
    inserted = true;
  } else {
    while (prev != tail_) {
      if (data <= prev->data && data > curr->data && !inserted) {
        prev->next = Node(data, curr);
        inserted = true;
      }
      prev = prev->next;
      curr = curr->next;
    }
  }
  if (!inserted) {
    prev->next = Node(data, curr);
    tail_ = prev->next;
  }
  prev = nullptr;
  curr = nullptr;
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (head_ != nullptr) {
    if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
    } else {
      node_order_ = Order::kASC;
    }
    Node<T>* prev = head_;
    Node<T>* curr = head_->next;
    Node<T>* next = head_->next->next;
    while (curr != head_) {
      curr->next = prev;
      prev = curr;
      curr = next;
      next = curr->next;
    }
    curr->next = prev;
    
    prev = nullptr;
    curr = nullptr;
    next = nullptr;
  }
}



#endif
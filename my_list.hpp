#pragma once

#include <iostream>
#include <memory>

template <typename T> class list {
  struct node {
    T data{};
    std::unique_ptr<node> next;
    node *prev{};

    node() = default;
    node(int data_) : data{data_}, next{nullptr}, prev{nullptr} {}
  };

  std::unique_ptr<node> head;
  node *current{};
  size_t size_{};

public:
  using iterator = node *;
  using const_iterator = const node *;
  using reference = T &;
  using const_reference = const T &;

  iterator begin() { return head; }
  iterator end() { return current; }
  const_iterator begin() const { return head; }
  const_iterator end() const { return current; }

  size_t size() const { return size_; }

  void push_front(T value) {
    auto tmpNode = std::make_unique<node>(value);
    tmpNode->data = value;
    tmpNode->next = std::move(head);
    if (head == nullptr) {
      current = std::move(tmpNode);
      head = tmpNode.get();
    }
    head = tmpNode.get();
  }
};

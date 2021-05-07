#pragma once

#include <cassert>
#include <iostream>
#include <memory>

template <typename T> class List {
  struct node {
    T data{};
    std::unique_ptr<node> next;
    node *prev{};

    node() = default;
    explicit node(const T &data_) : data{data_}, next{nullptr}, prev{nullptr} {}
    explicit node(T &&data_)
        : data{std::move(data_)}, next{nullptr}, prev{nullptr} {}
  };

  std::unique_ptr<node> head;
  node *current{};
  size_t size_{};

public:
  using iterator = node *;
  using const_iterator = const node *;
  using reference = T &;
  using const_reference = const T &;

  iterator begin() { return head.get(); }
  iterator end() { return current; }
  const_iterator begin() const { return head.get(); }
  const_iterator end() const { return current; }

  size_t size() const { return size_; }
  reference front() { return head->data; }
  const_reference front() const { return head->data; }
  reference back() { return current->data; }
  const_reference back() const { return current->data; }
  bool empty() const { return head == nullptr; }

  void push_front(const T &value) {
    auto tmpNode = std::make_unique<node>(value);
    if (head == nullptr) {
      head = std::move(tmpNode);
      current = head.get();
    } else {
      head->prev = tmpNode.get();
      tmpNode->next = std::move(head);
      head = std::move(tmpNode);
    }
    ++size_;
  }

  void push_front(T &&value) {
    auto tmpNode = std::make_unique<node>(std::move(value));
    if (head == nullptr) {
      head = std::move(tmpNode);
      current = head.get();
    } else {
      head->prev = tmpNode.get();
      tmpNode->next = std::move(head);
      head = std::move(tmpNode);
    }
    ++size_;
  }

  void push_back(const T &value) {
    auto tmpNode = std::make_unique<node>(value);
    if (head == nullptr) {
      head = std::move(tmpNode);
      current = head.get();
    } else {
      tmpNode->prev = current;
      current->next = std::move(tmpNode);
      current = (current->next).get();
    }
    ++size_;
  }

  void push_back(T &&value) {
    auto tmpNode = std::make_unique<node>(std::move(value));
    if (head == nullptr) {
      head = std::move(tmpNode);
      current = head.get();
    } else {
      tmpNode->prev = current;
      current->next = std::move(tmpNode);
      current = (current->next).get();
    }
    ++size_;
  }

  template <typename... Args> void emplace_back(Args &&...args) {
    auto tmpNode = std::make_unique<node>(T{std::forward<Args>(args)...});
    if (head == nullptr) {
      head = std::move(tmpNode);
      current = head.get();
    } else {
      tmpNode->prev = current;
      current->next = std::move(tmpNode);
      current = (current->next).get();
    }
    ++size_;
  }

  void pop_back() {
    assert(!empty());
    if (head.get() == current) {
      head.release();
      delete current;
    } else {
      current = current->prev;
      auto tmpPtr = (current->next).release();
      delete tmpPtr;
    }
    --size_;
  }
};

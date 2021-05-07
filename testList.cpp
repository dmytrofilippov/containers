#include "my_list.hpp"

#include <iostream>
#include <list>

#include "catch2/catch.hpp"

TEST_CASE("test list") {

  List<int> list;

  CHECK(list.begin() == nullptr);
  CHECK(list.end() == nullptr);
  CHECK(list.size() == 0);
  CHECK(list.empty() == true);

  list.push_front(5);
  list.push_front(4);
  list.push_front(3);

  CHECK(list.front() == 3);
  CHECK(list.back() == 5);
  CHECK(list.empty() == false);

  SECTION("testing push_front") {

    CHECK(list.begin()->data == 3);
    CHECK(list.begin()->next->data == 4);
    CHECK(list.end()->data == 5);
    CHECK(list.end()->prev->data == 4);
    CHECK(list.size() == 3);
  }

  SECTION("testing push_back") {

    list.push_back(20);
    list.push_back(30);

    CHECK(list.end()->data == 30);
    CHECK(list.end()->prev->data == 20);
    CHECK(list.size() == 5);

    List<int> list2;

    list2.push_back(25);
    list2.push_back(35);

    CHECK(list2.begin()->data == 25);
    CHECK(list2.begin()->next->data == 35);
    CHECK(list2.end()->data == 35);
  }

  SECTION("testing pop_back") {

    list.pop_back();

    CHECK(list.back() == 4);
    CHECK(list.size() == 2);

    list.pop_back();

    CHECK(list.back() == 3);
    CHECK(list.size() == 1);

    list.pop_back();

    CHECK(list.empty() == true);
    CHECK(list.size() == 0);
  }
}

struct Test {
  int value{};

  Test() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  Test(int value_) : value(value_) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  Test(const Test &rhs) : value(rhs.value) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  Test(Test &&rhs) : value(std::move(rhs.value)) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};

TEST_CASE("testing emplace") {

  List<Test> list3;

  list3.emplace_back(4);
  list3.emplace_back(44);
  list3.emplace_back(55);

  CHECK(list3.begin()->data.value == 4);
  CHECK(list3.begin()->next->data.value == 44);
  CHECK(list3.end()->data.value == 55);
  CHECK(list3.end()->prev->data.value == 44);
}
#include "my_list.hpp"

#include <iostream>

#include "catch2/catch.hpp"

TEST_CASE("test list") {

  list<int> list;

  CHECK(list.begin() == nullptr);
  CHECK(list.end() == nullptr);
  CHECK(list.size() == 0);

  list.push_front(3);
  list.push_front(4);
  list.push_front(5);

  CHECK(list.begin()->data == 5);
  CHECK(list.begin()->next->data == 4);
  CHECK(list.end()->data == 3);
  CHECK(list.end()->prev->data == 4);
  CHECK(list.size() == 3);
}
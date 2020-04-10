#include <catch2/catch.hpp>
#include "../platformer.hpp"

TEST_CASE("Add 5 to num") {
  int a = 0;
  guy main_guy;
  REQUIRE(main_guy.add_5(a) == 10);
}

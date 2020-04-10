#include <catch2/catch.hpp>
#include "../src/map.hpp"

TEST_CASE("Create character") {
  int width = 480;
  int height = 680;
  map m(x, y);
  REQUIRE(main_guy.get_x_cord() == 480);
  REQUIRE(main_guy.get_y_cord() == 680);
}

TEST_CASE("Set new cord for character") {
  int x = 0;
  int y = 1;
  guy main_guy(x, y);
  main_guy.set_x_cord(10);
  main_guy.set_y_cord(11);
  REQUIRE(main_guy.get_x_cord() == 10);
  REQUIRE(main_guy.get_y_cord() == 11);
}

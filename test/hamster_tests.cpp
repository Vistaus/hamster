#define CATCH_CONFIG_MAIN

#include "catch.hpp"

TEST_CASE("first test case", "[hamster_tests]")
{
    REQUIRE(1 == 1);
}

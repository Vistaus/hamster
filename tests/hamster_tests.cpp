#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "hamster.h"


TEST_CASE("first test case", "[hamster_tests]")
{
    REQUIRE(1 == 1);
}

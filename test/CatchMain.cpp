/** @file CatchMain.cpp
 * @autor       : Mikael Nilsson
 * Description : Används för att minska på kompieringstiden genom
 * att definera CATCH_CONFIG_MAIN i en kompileringsenhet
 * som aldrig ändras och därför aldrig behöver kompileras om.
 *
*/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

SCENARIO("Hello Test")
{
    GIVEN("A valid configuration")
    {
        THEN("The first test should fail!")
        {
            REQUIRE(false);
        }
    }
}
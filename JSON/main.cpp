#define CATCH_CONFIG_MAIN
#include "json.hpp"
#include <exception>
#include "catch.hpp"

TEST_CASE("Test json write and read")
{
    std::string json = "{\"lastname\" : \"Ivanov\",\"firstname\" : \"Ivan\",\"age\" : 25,\"islegal\" : false,\"marks\" : [        4,5,5,5,2,3    ],\"address\" : {\"city\" : \"Moscow\",\"street\" : \"Vozdvijenka\"    }}" ;
    Json object = Json::parse(json);
    REQUIRE(std::any_cast<std::string>(object["lastname"]) == "Ivanov");
    REQUIRE(std::any_cast<bool>(object["islegal"]) == false);
    REQUIRE(std::any_cast<int>(object["age"])==25);
    
    auto marks = std::any_cast<Json>(object["marks"]);
    REQUIRE(std::any_cast<int>(marks[0]) == 4);
    REQUIRE(std::any_cast<int>(marks[1]) == 5);
    
    auto address = std::any_cast<Json>(object["address"]);
    REQUIRE(std::any_cast<std::string>(address["city"]) == "Moscow");
    REQUIRE(std::any_cast<std::string>(address["street"]) == "Vozdvijenka");
}

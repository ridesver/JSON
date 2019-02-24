#include <iostream>
#include "JSON_lib.hpp"
int main(int argc, const char * argv[]) {
    std::string json = "{\"lastname\" : \"Ivanov\",\"firstname\" : \"Ivan\",\"age\" : 25,\"islegal\" : false,\"marks\" : [        4,5,5,5,2,3    ],\"address\" : {\"city\" : \"Moscow\",\"street\" : \"Vozdvijenka\"    }}" ;
    Json object = Json::parse(json);
    std::cout<<std::any_cast<std::string>(object["lastname"])<<'\n';
    return 0;
}

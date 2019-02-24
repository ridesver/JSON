//
//  main.cpp
//  JSON_for_modernC++

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
int main(int argc, const char * argv[]) {
     auto j = json::array();
     j = R"([
     ["Si-9.15", "RTS-9.15", "GAZP-9.15"],
     [100024, 100027, 100050],
     ["Futures contract for USD/RUB", "Futures contract for index RTS", "Futures contract for Gazprom shares"]
    ])"_json;
    json arr = json::array();
    for (std::size_t i = 0; i < j[0].size(); ++i) {
        json tmp;
        tmp["ticker"] = j[0][i];
        tmp["id"] = j[1][i];
        tmp["description"] = j[2][i];
        //std::cout << tmp.dump(4) << std::endl;
        arr.push_back(tmp);
    }
    std::cout<<arr<<'\n';
    return 0;
}

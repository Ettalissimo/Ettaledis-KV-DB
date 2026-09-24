#include "../include/request_processor.hpp"
#include <vector>
#include <string>
#include <optional>
#include "../include/store.hpp"
#include <iostream>


std::vector<std::string> request_processor(const std::vector<Command>& commands,Store& store){
//Store& (non-const, since set/del mutate it) and const std::vector<Command>& for read-only access without copying.
    std::cout << "prob processrpr "<< std::endl;
    std::vector<std::string> response;
    std::string res;

    for(const Command& com : commands ){ //const because we are just reading no need to have a copy each time
        if (com.keyword == "set"){
            store.set(com.args[0],com.args[1]);
            res = "SET operation done.";
        } else if (com.keyword == "get"){
            std::optional<std::string> res_inter = store.get(com.args[0]);
            if (!res_inter.has_value()){
                res = "NOT FOUND!";
            } else {
                res = res_inter.value();
            }
        } else if (com.keyword == "del"){
            bool bool_v = store.del(com.args[0]);
            if (!bool_v){
                res = "NOT FOUND!";
            } else {
                res = "Delete Done!";
            }
        }
        response.push_back(res);
    }
    std::cout << "prob processr 2 "<< std::endl;

    return response;
}
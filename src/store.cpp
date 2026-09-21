#include <string>
#include <optional>
#include "../include/store.hpp"
#include <iostream>

bool Store::del(const std::string& key){
    if (Store::m_data.count(key)){
        std::cout << "key exists " << '\n';
        Store::m_data.erase(key);
        return true;
    }
    else{
        std::cout << "Not found\n";
        return false;
    };
}; 
        
std::optional<std::string> Store::get(const std::string& key){
    return Store::m_data.at(key);
};

void Store::set(const std::string& key, const std::string& value){
    Store::m_data[key] = value;
};
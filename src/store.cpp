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
    // return Store::m_data.at(key);
    // why no longer use at : But for Get, where "not found" is expected/valid input 
    // (not an error condition), .at() is the wrong tool since it throws instead of 
    // letting you return std::nullopt.

    auto it = m_data.find(key);
    if (it != m_data.end()){
        return it->second;
    } else {
        return std::nullopt;
    }

};

void Store::set(const std::string& key, const std::string& value){
    Store::m_data[key] = value;
};
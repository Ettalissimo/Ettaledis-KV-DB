#pragma once
#include <string>
#include <optional>
#include <unordered_map>

class Store{
    private:
        std::unordered_map<std::string,std::string> m_data;
    public:
        bool del(const std::string& key); 
        
        std::optional<std::string> get(const std::string& key);

        void set(const std::string& key, const std::string& value);
        // at this stage adding or updating in the hashmap never fails so no need to return a success/fail bool
};
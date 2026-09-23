#pragma once
#include <string>
#include <vector>

struct Command{
    std::string keyword;
    std::vector<std::string> args; //set has 2 args others 1 arg
};

std::vector<Command> request_validator(const std::string& request);
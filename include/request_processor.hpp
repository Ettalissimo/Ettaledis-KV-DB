#pragma once
#include "../include/request_validator.hpp"
#include <vector>
#include <string>


td::vector<std::string> request_processor(std::vector<Command> commands);
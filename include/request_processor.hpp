#pragma once
#include "../include/request_validator.hpp"
#include <vector>
#include <string>


std::vector<std::string> request_processor(const std::vector<Command>& commands,Store& store);
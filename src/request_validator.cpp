#include "../include/request_validator.hpp"
#include <string>
#include <vector>
#include <iostream>

std::vector<Command> input_validator(const std::string &request){
    // tokenize → check keyword → check arity → dispatch

    std::vector<std::string> request_vector;
    std::vector<std::vector<std::string>> command_vector;
    std::vector<Command> commands;
    std::string tkn;
    for( char x : request){ 
        if (x == ' ' ){
            request_vector.push_back(tkn);
            tkn = "";
        } else if( x == '\n'){
            request_vector.push_back(tkn);
            command_vector.push_back(request_vector);
            request_vector = {};
        }else{
            x = std::tolower(static_cast<unsigned char>(x)); // case insensitive
            tkn+=x;
        }
    }

    for (std::vector<std::string> x : command_vector){
        Command com;
        if (x.size() == 3 and x[0] == "set"){
            com.keyword = x[0];
            com.args.push_back(x[1]);
            com.args.push_back(x[2]);
        } else if (x.size() == 2 and (x[0] == "get" or x[0] == "del")){
            com.keyword = x[0];
            com.args.push_back(x[1]);
        } else {
            std::cout << "Command invalid: \nHere is the format to follow: \nSET key value \nGET key \nDEL key"<< std::endl ;
            continue;
        }
        commands.push_back(com);
    }

    return commands;

};

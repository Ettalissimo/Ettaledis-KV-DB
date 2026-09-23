#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
int main(){
    const int PORT = 8080;

    // 1- create a TCP socket
    int server_fd = socket(AF_INET,SOCK_STREAM,0);
    if (server_fd<0){
        std::cerr << "Failed to create socket \n";
        return 1;
    }

    //Allow quick reuse of the port after restart (avoids "Qddress already in use")
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    // this line solves this issue:
    // When a TCP connection closes, the operating system doesn't free up the port immediately. It holds onto it for a minute or so, just in case some old, delayed network packets are still floating around and need to be handled. This is a safety feature of TCP called TIME_WAIT.


    //2- bind to an addresses/port
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // listen on all interfaces (Accept connections on any IP.)
    address.sin_port = htons(PORT);        // host-to-network byte order

    //htons(): Converts port to network byte order.
    

    // "Binding" means assigning a specific IP address and port number to a socket, so the operating system knows: "this socket is the one that should receive traffic sent to this address/port."
    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0 ){
        std::cerr <<"Bind failed\n";
        close(server_fd);
        return 1;
    }

    // 3- Listen for incoming connections
    // Allow up to 5 clients to be waiting in the queue, ready to be accepted, at the same time."
    if (listen(server_fd, /*backlog=*/5)<0){
        std::cerr << "Listen failed\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Server listening on port " << PORT << "...\n";

    while (true){
        // 4- accept a cliemt connection (blocks untill one arrives)
        sockaddr_in client_addr {};
        socklen_t client_len = sizeof(client_addr);

        int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
        if (client_fd < 0){
            std::cerr << "Accepted failed \n";
            continue;
        }

        std::cout << "Client connected: "
                  <<  inet_ntoa(client_addr.sin_addr) << ":"
                  <<  ntohs(client_addr.sin_port) << "\n";
        
        // 5- read a request from client
        char buffer[1024] = {0};
        recv(client_fd, buffer, sizeof(buffer), 0);
        std::cout << "Request from client: " << buffer << std::endl;

        //6- send data back to client
        std::string response = " "; // to fill later
        send(client_fd, response.c_str(), response.size(), 0);

        //7- close this client s connection
        close(client_fd);
    }

    close(server_fd); // never reached in this loop, but good practice
    return 0;

}
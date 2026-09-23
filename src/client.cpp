#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
    const char* SERVER_IP = "127.0.0.1";
    const int PORT = 8080;

    // 1. Create a TCP socket
    // AF_INET → IPv4 addresses (e.g. 192.168.1.1)
		// AF_INET6 → IPv6 addresses (e.g. 2001:db8::1)
		
		// SOCK_STREAM (tcp) : Socket Type
		// SOCK_DGRAM → UDP
		// SOCK_RAW → raw sockets — direct access to lower-level protocols (e.g. crafting your own IP/ICMP packets), typically requires elevated privileges.
    int sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }


    // 2. Specify server address
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);


    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address\n";
        close(sock);
        return 1;
    }

    //3- connect to the server
    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)),0){
        std::cerr <<"Connection failed \n";
        close(sock);
        return 1;
    }

    //4- send a request to the server
    std::string request = "get data"; //fill later
    send(sock,request.c_str(), request.size(),0);

    //5- Receive the server s response
    char buffer[1024] = {0};
    recv(sock, buffer,sizeof(buffer), 0);
    std::cout << "Server response: "<< buffer<< std::endl;

    //6-close the connection
    close(sock);
    return 0;
}
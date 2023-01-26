#include "header.h"

// const int PORT = 8000;
const int BACKLOG = 10;

void handle_client(int client_socket) {
    ClientInfo client_info;
    CLI cli(client_socket, client_info);
    cli.start();
    close(client_socket);
}


int main(int argc, char* argv[]) {
int PORT = atoi(argv[1]);
int server_fd = socket(AF_INET, SOCK_STREAM, 0);
if (server_fd < 0) {
std::cerr << "Error creating socket" << std::endl;
return 1;
}

// Set up the server address and port
sockaddr_in server_address;
memset(&server_address, 0, sizeof(server_address));
server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = INADDR_ANY;
server_address.sin_port = htons(PORT);

// Bind the socket to the address and port
if (bind(server_fd, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
std::cerr << "Error binding socket" << std::endl;
return 1;
}

// Listen for incoming connections
if (listen(server_fd, BACKLOG) < 0) {
std::cerr << "Error listening for connections" << std::endl;
return 1;
}

while (true) {
sockaddr_in client_address;
socklen_t client_address_len = sizeof(client_address);
int client_fd = accept(server_fd, (sockaddr*)&client_address, &client_address_len);
if (client_fd < 0) { std::cerr << "Error accepting connection" << std::endl; }
std::cout << "Accepted connection from " << inet_ntoa(client_address.sin_addr) << std::endl;
std::thread t(handle_client, client_fd);
t.detach();
}
close(server_fd);
return 0;
}


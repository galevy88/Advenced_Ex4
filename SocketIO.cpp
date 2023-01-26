#include "header.h"
std::mutex mutex_;

SocketIO::SocketIO(int socket) : socket_(socket) {}

    std::string SocketIO::Read() {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        std::string message;
        int bytes_received = 0;
        int buffer_size = 4096;
        char * buffer = new char[buffer_size];
        bytes_received = recv(socket_, buffer, buffer_size, 0);

        message.append(buffer, bytes_received);
        // std::cout << message.size() << std::endl;
        delete[] buffer;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        return message;
    }

    void SocketIO::Write(const std::string &message) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        send(socket_, message.c_str(), message.size(), 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

#include <iostream>
#include <regex>
#include <cstdlib>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>

void runClient(const std::string& ip, int& port){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error al crear el socket\n";
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "IP inválida\n";
    }

    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error al conectar\n";
    }
    std::string request = "GET /status HTTP/1.1\r\nHost: " + ip + "\r\nConnection: close\r\n\r\n";

    send(sock, request.c_str(), request.length(), 0);

    char buffer[4096];
    ssize_t bytesReceived;
    while ((bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << buffer;
    }
     close(sock);
}

void validarIP(const std::string& ip) {
    std::regex ipRegex(R"(^((25[0-5]|(2[0-4][0-9])|(1[0-9][0-9])|([1-9]?[0-9]))\.){3}(25[0-5]|(2[0-4][0-9])|(1[0-9][0-9])|([1-9]?[0-9]))$)");
    if (!std::regex_match(ip, ipRegex)) {
        std::cerr << "IP inválida: " << ip << "\n";
        exit(1);
    }
}

void validarPuerto(int port) {
    if (port < 1 || port > 65535) {
        std::cerr << "Puerto fuera de rango (1–65535): " << port << "\n";
        exit(1);
    }
}
 
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << "<ip> <port>" << std::endl;
        return 1;
    }

    int port;
    const std::string ip = argv[1];
    port = std::atoi(argv[2]);
    validarIP(ip);
    validarPuerto(port);
    runClient(ip,port);

    return 0;
}



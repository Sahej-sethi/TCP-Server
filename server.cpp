#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("Socket Failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    int bd = bind(fd, (const sockaddr*)&addr, sizeof(addr));
    if (bd < 0) {
        perror("Bind Failed");
        exit(EXIT_FAILURE);
    }

    int ld = listen(fd, 10);
    if (ld < 0) {
        perror("Listen Failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int ad = accept(fd, (sockaddr*)&client_addr, &client_len);
        if (ad < 0) {
            perror("Accept Failed");
            continue; 
        } else {
            cout << ad << endl;
            cout << inet_ntoa(client_addr.sin_addr) << endl;
            cout << ntohs(client_addr.sin_port) << endl;

            char buffer[3000] = {}; 
            int val_read = recv(ad, buffer, sizeof(buffer), 0);

            if (val_read > 0) {
                cout << "Success! Read " << val_read << " bytes.\n";
            } else if (val_read == 0) {
                cout << "Client disconnected.\n";
            } else {
                perror("Error reading data");
            }

            const char* hello = 
                "HTTP/1.1 200 OK\r\n"           
                "Content-Type: text/html\r\n"   
                "\r\n"                          
                "<h1>Hello from your C++ Server!</h1>"; 

            if (send(ad, hello, strlen(hello), 0) < 0) {
                perror("Send failed");
            } else {
                cout << "Response sent to Client." << endl;
            }
            
            close(ad);
        } 
    }
    
    return 0;
}
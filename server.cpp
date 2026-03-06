#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
using namespace std;

void handle_client(int client_fd){
    
    char s[3000];
    int v = recv(client_fd,s,sizeof(s),0);
    if(v<0){
        perror("Recv Failed!");
    }else{
        
        const char* body = "<h1>Hello from a Parallel C++ Worker Thread!</h1>";
        string response = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Content-Length: " + to_string(strlen(body)) + "\r\n"
                          "\r\n" + 
                          string(body);
        
        send(client_fd,response.c_str(),response.size(),0);
    }
    close(client_fd);
}

int main(){
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd<0){
        perror("Socket Failed!");
        return EXIT_FAILURE;
    }

    sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    int bd = bind(fd,(struct sockaddr*)&addr,sizeof(addr));
    if(bd<0){
        perror("Bind Failed!");
        return EXIT_FAILURE;
    }

    int ld = listen(fd,10000);
    if(ld<0){
        perror("Listen Failed!");
        return EXIT_FAILURE;
    }

    while(true){
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int ad = accept(fd,(struct sockaddr*)&client_addr,&client_len);
        if(ad<0){
            perror("Accept Failed!");
            continue;
        }

        thread worker(handle_client,ad);

        worker.detach();
    }

}
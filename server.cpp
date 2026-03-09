#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<int> client_queue;      
mutex queue_mutex;            
condition_variable cv;        

void worker_loop() {
    while (true) {
        int my_customer_fd;
        {
            unique_lock<mutex> lock(queue_mutex);
            cv.wait(lock, [] { return !client_queue.empty(); });

            my_customer_fd = client_queue.front();
            client_queue.pop();
            
        } 

        char s[3000] = {0};
        int v = recv(my_customer_fd, s, sizeof(s), 0);
        
        if (v < 0) {
            perror("Recv Failed!");
        } else {
            const char* body = "<h1>Phase 3 Thread Pool is Online!</h1>";
            string response = "HTTP/1.1 200 OK\r\n"
                              "Content-Type: text/html\r\n"
                              "Content-Length: " + to_string(strlen(body)) + "\r\n"
                              "\r\n" + 
                              string(body);
            
            send(my_customer_fd, response.c_str(), response.size(), 0);
        }
        close(my_customer_fd);
    }
}

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){ 
        perror("Socket Failed!"); return EXIT_FAILURE; 
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    int bd = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if(bd < 0){ 
        perror("Bind Failed!"); return EXIT_FAILURE; 
    }

    int ld = listen(fd, 10000);
    if(ld < 0){ 
        perror("Listen Failed!"); return EXIT_FAILURE; 
    }

    for (int i = 0; i < 7; i++) {
        thread worker(worker_loop);
        worker.detach(); 
    }

    while(true){
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int client_fd = accept(fd, (struct sockaddr*)&client_addr, &client_len);
        if(client_fd < 0){
            perror("Accept Failed!");
            continue; 
        }

        {
            lock_guard<mutex> lock(queue_mutex);
            client_queue.push(client_fd);
        } 
        cv.notify_one(); 
    }

    return EXIT_SUCCESS;
}
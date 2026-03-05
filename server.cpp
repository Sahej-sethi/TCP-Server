#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_ntoa converts addr to string
#include <unistd.h> // for close
using namespace std;

int main(){

    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd<0) cout << "Socket Failed\n";
    else cout << fd << endl;

    sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    int bd = bind(fd,(const sockaddr*)&addr,sizeof(addr));
    if(bd<0) cout << "Bind Failed\n";
    else cout << bd << endl;

    int ld = listen(fd,10);
    if(ld<0) cout << "Listen Failed\n";
    else cout << ld << endl;

    while(true)
    {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);//provided 16 bytes for IPv4 do not write more than that
        int ad = accept(fd,(sockaddr*)&client_addr,&client_len);
        if(ad<0) cout << "Accept Failed\n";
        else{
            cout << ad << endl;
            cout << inet_ntoa(client_addr.sin_addr) << endl;
            cout << ntohs(client_addr.sin_port) << endl;//Network to host endianess flip, random port given by browser
            //Process
            char buffer[3000] = {}; //No string since c based library
            int val_read = recv(ad,buffer,sizeof(buffer),0);

            if (val_read > 0) {
                cout << "Success! Read " << val_read << " bytes.\n";
            } else if (val_read == 0) {
                cout << "Client disconnected.\n";
            } else {
                cerr << "Error reading data.\n";
            }

            //Send Response
            const char* hello = 
                "HTTP/1.1 200 OK\r\n"           // Status: Success
                "Content-Type: text/html\r\n"   // Header: It's HTML
                // "Content-Length: 46\r\n"        // Header: Size (Optional but good)
                "\r\n"                          // Blank Line (Required!)
                "<h1>Hello from your C++ Server!</h1>"; // Body

            // send(Socket, Message, Length, Flags)
            send(ad, hello, strlen(hello), 0); 
            cout << "Response sent to Client." << endl;
            //Free the fd
            close(ad);
        } 
    }
    return 0;
}
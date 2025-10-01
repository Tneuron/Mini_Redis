#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
#define PORT 8080
#define BACKLOG 5

int main(){
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len;
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<=0){
        cout << "Socket creation failed" << endl;
        exit(0);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(PORT);

    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))){
        cout << "Connection to the server failed" << endl;
        exit(0);
    }
    cout << "Connected to the server!!!" << endl;

    char buffer[1024];
    while(true){
        cout << "Enter input string (type EXIT to quit):";
        string msg;
        getline(cin, msg);         
        if (msg=="EXIT") break;   
        send(sockfd, msg.c_str(), msg.size(), 0);  
        memset(buffer, 0, sizeof(buffer));
        int n=read(sockfd, buffer, sizeof(buffer));
        if(n>0){
            cout << "Server: " << buffer;
        }
        cout << endl;
    }

    close(sockfd);
    return 0;
    
}
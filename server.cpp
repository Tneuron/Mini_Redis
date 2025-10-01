#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "parser.h"
#include "json_store.h"
using namespace std;

#define PORT 8080
#define BACKLOG 5

void handle_client(int connfd){
    char buffer[1024];
    while(true){
        memset(buffer, 0, sizeof(buffer));
        int n=read(connfd, buffer, sizeof(buffer));
        if(n<=0) break;
        cout << "Client: " << buffer << endl;
        string cmd(buffer);
        cmd.erase(cmd.find_last_not_of("\r\n")+1);
        if(cmd=="SAVE"){
            saveJson(SNAPSHOT_DB);
        }
        string response=parseString(cmd);
        cout << "Server: " << response << endl;
        send(connfd, response.c_str(), response.size(), 0);
    }
    close(connfd);
}

int main(){
    checkJson(SNAPSHOT_DB);
    loadJson(SNAPSHOT_DB);
    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len=sizeof(cliaddr);
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){
        cout << "Socket creation failed" << endl;
        exit(0);
    }
    cout << "Connecting to the client..." << endl;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(PORT);
    memset(&cliaddr, 0, sizeof(cliaddr));

    int opt=1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))<0) {
        perror("setsockopt");
        exit(1);
    }
    if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))){
        cout << "Socket bind failed" << endl;
        exit(0);
    }
    if(listen(sockfd, BACKLOG)){
        cout << "Listen failed" << endl;
        exit(0);
    }
    while(true){
        connfd=accept(sockfd, (struct sockaddr*)&cliaddr, &len);
        if(connfd<0){
            cout << "Server connection failed" << endl;
            exit(0);
        }
        cout << "Client connected!!!" << endl;
        thread(handle_client, connfd).detach();
    }
    close(sockfd);
    return 0;
}
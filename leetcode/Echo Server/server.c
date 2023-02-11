#include <iostream>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void* task(void* arg) {
    int newSocket = *((int*)arg);
    char buffer[256];
    int n;
    while (true) {
        bzero(buffer,256);
        n = read(newSocket,buffer,255);
        if (n < 0) {
            std::cout << "Error reading from socket" << std::endl;
            exit(1);
        }
        std::cout << "Received: " << buffer << std::endl;
        n = write(newSocket,buffer,strlen(buffer));
        if (n < 0) {
            std::cout << "Error writing to socket" << std::endl;
            exit(1);
        }
    }
}

int main(int argc, char* argv[]) {
    int serverSocket, newSocket;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    pthread_t tid;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cout << "Error opening socket" << std::endl;
        exit(1);
    }
    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serverSocket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Error on binding" << std::endl;
        exit(1);
    }
    listen(serverSocket,5);
    clilen = sizeof(cli_addr);
    while (true) {
        newSocket = accept(serverSocket, (struct sockaddr*) &cli_addr, &clilen);
        if (newSocket < 0) {
            std::cout << "Error on accept" << std::endl;
            exit(1);
        }
        pthread_create(&tid,NULL,task,&newSocket);
    }
    return 0;
}

#include<bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
using namespace std;

// Structure to hold information about each client
struct ClientInfo {
    int socket;
};

// Function to handle each client in a separate thread
void *handleClient(void *arg) {
    ClientInfo *clientInfo = (ClientInfo *)arg;
    int newSd = clientInfo->socket;
    char msg[1500];
    int bytesRead, bytesWritten = 0;

    while (1) {
        memset(&msg, 0, sizeof(msg));
        bytesRead += recv(newSd, (char *)&msg, sizeof(msg), 0);

        if (!strcmp(msg, "exit")) {
            cout << "Client has quit the session" << endl;
            break;
        }

        cout << "message from client: " << msg << endl;

        cout << "Enter message to send: ";
        string data;
        getline(cin, data);

        memset(&msg, 0, sizeof(msg));
        strcpy(msg, data.c_str());

        if (data == "exit") {
            // Send to the client that the server has closed the connection
            send(newSd, (char *)&msg, strlen(msg), 0);
            break;
        }

        bytesWritten += send(newSd, (char *)&msg, strlen(msg), 0);
    }

    // Close the client socket
    close(newSd);
    delete clientInfo;
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: port" << endl;
        exit(0);
    }

    int port = atoi(argv[1]);
    char msg[1500];

    sockaddr_in servAddr;
    bzero((char *)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);

    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSd < 0) {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }

    int bindStatus = bind(serverSd, (struct sockaddr *)&servAddr, sizeof(servAddr));
    if (bindStatus < 0) {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }

    cout << "Waiting for a client to connect..." << endl;

    listen(serverSd, 5);

    while (1) {
        sockaddr_in newSockAddr;
        socklen_t newSockAddrSize = sizeof(newSockAddr);
        int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);

        if (newSd < 0) {
            cerr << "Error accepting request from client!" << endl;
            exit(1);
        }

        cout << "Connected with client!" << endl;

        // Create a new thread to handle each client
        pthread_t tid;
        ClientInfo *clientInfo = new ClientInfo{newSd};
        if (pthread_create(&tid, NULL, handleClient, (void *)clientInfo) != 0) {
            cerr << "Error creating thread!" << endl;
            exit(1);
        }
    }

    close(serverSd);

    return 0;
}

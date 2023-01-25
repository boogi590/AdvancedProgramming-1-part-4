#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include "Command.h"
#include "Distance.h"
#include "InputValidation.h"
#include "DataBase.h"
#include "KNN.h"
#include "UploadCommand.h"
#include "SettingsCommand.h"
#include "FlowControl.h"
#include "ClassifyData.h"
#include "DisplayResults.h"

using namespace std;

void *handle_client(void *arg)
{
    string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n1. upload an unclassified csv data file\n2. algorithm settings\n3. classify data\n4. display result\n5. download results\n8. exit";

    int client_sock = *(int *)arg;
    SocketIO socket(client_sock);
    //************** client data ***********************************************************************************
    multimap<vector<double>, string> dataBase;
    vector<vector<double>> test;
    string distanceMatric = "AUC";
    int k = 5;
    FlowControl flowControl;
    map<int, string> classify_data;
    Command *commandArray[5];
    commandArray[0] = new UploadCommand(socket, dataBase, test);
    commandArray[1] = new SettingsCommand(socket, dataBase, k, distanceMatric);
    commandArray[2] = new ClassifyData(dataBase, test, k, distanceMatric, flowControl, classify_data);
    commandArray[3] = new DisplayResults(classify_data, flowControl);
    //************** end of client data *****************************************************************************
    while (true)
    {
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));
        int read_bytes = send(client_sock, menu.c_str(), menu.length(), 0);
        memset(buffer, 0, sizeof(buffer));
        // int expected_data_len = sizeof(buffer);
        read_bytes = recv(client_sock, buffer, sizeof(buffer), 0);

        if (read_bytes <= 0)
        {
            break;
        }
        else
        {
            // convert from char to int.
            int userChiose = buffer[0] - '0';
            if (InputValidation::menuCheck(userChiose))
            {
                cout << "database size =" << dataBase.size() << endl;
                cout << "test size=" << test.size() << endl;
                memset(buffer, 0, sizeof(buffer));
                commandArray[userChiose - 1]->execute();
            }
        }
    }
    close(client_sock);
    pthread_exit(NULL);
}

/*
 *creating a TCP server to accept from client vector, distance function and K for KNN algorithem. returning KNN result to client.
 *wating for clients to connet in infinite loop.
 */
int main(int argc, char *argv[])
{
    string classification;

    if (argc != 2)
    {
        cout << "wrong number of arguments. there should be 2 arguments" << endl;
        return 0;
    }

    int temp = 0;
    try
    {
        temp = stoi(argv[1]); // argv[2] should be the port to listen to.
    }
    catch (...)
    {
        cout << "port number is not valid \n";
        return 0;
    }

    const int server_port = temp;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("error binding socket");
    }
    if (listen(sock, 5) < 0)
    {
        perror("error listening to a socket");
    }
    while (true)
    {

        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *)&client_sin, &addr_len);
        if (client_sock < 0)
        {
            perror("error accepting client");
            continue;
        }

        // create a new thread to handle the client
        pthread_t thread;
        int rc = pthread_create(&thread, NULL, handle_client, (void *)&client_sock);
        if (rc)
        {
            perror("error creating thread");
            close(client_sock);
            continue;
        }
    }
    close(sock);
    return 0;
}
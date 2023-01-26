#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
#include "Distance.h"
#include "InputValidation.h"
#include "DataBase.h"
#include "KNN.h"
#include "UploadCommand.h"
#include "SettingsCommand.h"
#include "FlowControl.h"

using namespace std;

void *handle_client(void *arg)
{
    string menu = "Welcome to the KNN Classifier Server. Please choose an option:\n1. upload an unclassified csv data file\n2. algorithm settings\n3. classify data\n4. display result\n5. download results\n8. exit";

    int client_sock = *(int *)arg;
    SocketIO socket(client_sock);
    multimap<vector<double>, string> dataBase;
    vector<vector<double>> test;
    string distanceMatric = "AUC";
    int k = 5;
    FlowControl flowControl;
    while (true)
    {
        DataBase::printDataBase(dataBase);
        DataBase::printTrainFile(test);
        cout << "dataBase size" << dataBase.size() << endl;
        cout << "test size" << test.size() << endl;

        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));
        int read_bytes = send(client_sock, menu.c_str(), menu.length(), 0);

        bool invalidFlag = false;
        string classification = "invalid input";
        memset(buffer, 0, sizeof(buffer));

        int expected_data_len = sizeof(buffer);
        read_bytes = recv(client_sock, buffer, sizeof(buffer), 0);

        if (read_bytes == 0)
        {
            break;
        }
        else if (read_bytes < 0)
        {
            invalidFlag = true;
            classification = "invalid input";
        }
        else
        {
            if (strlen(buffer) == 1 && buffer[0] == '1')
            {
                memset(buffer, 0, sizeof(buffer));
                UploadCommand command(socket, dataBase, test, flowControl);
                command.execute();
            }

            if (strlen(buffer) == 1 && buffer[0] == '2')
            {
                memset(buffer, 0, sizeof(buffer));
                SettingsCommand settingCommand(socket, dataBase, k, distanceMatric);
                settingCommand.execute();
            }

            // handle other menu options
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

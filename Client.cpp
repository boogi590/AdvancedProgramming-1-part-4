#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <limits>
#include <netinet/in.h>
#include <arpa/intet.h>
#include "InputValidation.h"
#include "ReadWriteFiles.h"
using namespace std;
#define MENU_SIZE 187

void *writeData(void *sock)
{
    int socketID = *(int *)sock;
    char buffer[4096];
    // recving and printing the command 5 description.
    recv(socketID, buffer, sizeof(buffer), 0);
    cout << buffer << endl;
    string address;
    cin >> address;
    memset(buffer, 0, sizeof(buffer));
    // Receive the file
    recv(socketID, buffer, sizeof(buffer), 0);
    ReadWriteFiles ::writeToFile(buffer, address);
}

int main(int argc, char *argv[])
{
    /*********************************CHECK THE ARGS*******************************/
    const char *ip_address = argv[1];
    // CHECK if the the user entered a valid IP address:
    // output buffer for the binary representation of the IP address
    in_addr output;
    if (inet_pton(AF_INET, ip_address, &output) != 1)
    {
        cout << "Invalid IP address" << endl;
        return 0;
    }
    // CHECK if the port is valid:
    //  stoi throws exception.
    int temp = 0;
    try
    {
        temp = stoi(argv[2]);
    }
    catch (...)
    {
        cout << "port number is not valid \n";
        return 0;
    }
    const int port_number = temp;
    /*************************************END OF CHECKS**********************************/

    // AF_INET = IPv4, SOCK_STREAM = TCP.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("error creating socket");
    }
    struct sockaddr_in sin;
    // reset all the members of the struct to 0.
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_number);
    // connect < 0 means that error occured.
    if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("error connecting to server");
    }
    // connected to server succesfully.
    int stop;
    int data_len;
    string userChoise;
    while (true)
    {
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));
        // receving the menu.
        recv(sock, buffer, MENU_SIZE, 0);
        cout << buffer << endl;
        // saving the menu.
        string menu = string(buffer, MENU_SIZE);
        memset(buffer, 0, sizeof(buffer));
        getline(cin, userChoise);
        while (userChoise.empty() || !userChoise.compare(""))
        {
            getline(cin, userChoise);
        }

        while (!InputValidation::menuCheck(stoi(userChoise)))
        {
            cout << "invalid userChoise" << endl;
            cout << menu << endl;
            getline(cin, userChoise);
        }
        try
        {
            stop = stod(userChoise);
            if (stop == -1)
            {
                break;
            }
        }
        catch (...)
        {
        }

        // sending the userChoise from the menu to the server.
        data_len = userChoise.length();
        int sent_bytes = send(sock, userChoise.c_str(), data_len, 0);
        if (sent_bytes < 0)
        {
            perror("error in sending");
        }

        // command 1 = reading the file and sending it to the server.
        if (data_len == 1 && userChoise == "1")
        {
            recv(sock, buffer, sizeof(buffer), 0);
            cout << buffer << endl;
            string fileName;
            cin >> fileName;

            ifstream file(fileName, ios::binary);
            if (!file)
            {
                int size = 0;
                cout << "invalid input" << endl;
                send(sock, (char *)&size, sizeof(size), 0);

                continue;
            }

            // Get the file size
            file.seekg(0, file.end);
            int fileSize = file.tellg();
            file.seekg(0, file.beg);

            // Send the file size
            send(sock, (to_string(fileSize)).c_str(), to_string(fileSize).length(), 0);
            // Send the file
            char buffer[4096];
            while (file)
            {
                memset(buffer, 0, sizeof(buffer));

                file.read(buffer, sizeof(buffer));
                int bytes_read = file.gcount();
                send(sock, buffer, bytes_read, 0);
            }
            file.close();
            memset(buffer, 0, sizeof(buffer));
            recv(sock, buffer, sizeof(buffer), 0);
            cout << buffer << endl;

            string fileNameTrain;
            cin >> fileNameTrain;

            ifstream fileTrain(fileNameTrain, ios::binary);
            if (!fileTrain)
            {
                int size = 0;
                cout << "invalid input" << endl;
                send(sock, (char *)&size, sizeof(size), 0);

                continue;
            }

            // Get the file size
            fileTrain.seekg(0, fileTrain.end);
            int fileSizeTrain = fileTrain.tellg();
            fileTrain.seekg(0, fileTrain.beg);

            // Send the file size
            send(sock, (to_string(fileSizeTrain)).c_str(), to_string(fileSizeTrain).length(), 0);

            // Send the file
            memset(buffer, 0, sizeof(buffer));

            while (fileTrain)
            {
                memset(buffer, 0, sizeof(buffer));

                fileTrain.read(buffer, sizeof(buffer));
                int bytes_read = fileTrain.gcount();
                cout << bytes_read;

                send(sock, buffer, bytes_read, 0);
            }
            fileTrain.close();
            memset(buffer, 0, sizeof(buffer));

            // recive Upload complete.
            recv(sock, buffer, sizeof("Upload complete.\n"), 0);
            cout << buffer;
        }

        if (data_len == 1 && userChoise == "2")
        {
            char buffer[4096];

            memset(buffer, 0, sizeof(buffer));

            // get bytes in the size of the description
            recv(sock, buffer, 65, 0);
            cout << buffer;
            memset(buffer, 0, sizeof(buffer));

            string newParms;
            getline(cin, newParms);

            if (newParms.length() == 0)
            {
                send(sock, "EMPTY", 5, 0);
                continue;
            }
            else
            {
                send(sock, newParms.c_str(), newParms.length(), 0);
            }
            memset(buffer, 0, sizeof(buffer));

            recv(sock, buffer, 45, 0);
            string answer = string(buffer, 7);
            if (answer != "changed")
            {
                cout << buffer;
            }
            memset(buffer, 0, sizeof(buffer));
        }

        if (data_len == 1 && userChoise == "5")
        {
            // create a new thread to handle the client
            pthread_t thread;
            int createSucessfully = pthread_create(&thread, NULL, writeData, (void *)sock);
            if (createSucessfully)
            {
                perror("error creating thread");
                close(sock);
                continue;
            }
        }
        if (data_len == 1 && userChoise == "8")
        {
            break;
        }
    }
    close(sock);
    return 0;
}

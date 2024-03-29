#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <limits>
#include "InputValidation.h"
using namespace std;
#define MENU_SIZE 187

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
        int choise = 0;
        do
        {
            try
            {
                choise = stoi(userChoise);
            }
            catch (...)
            {
                cout << "invalid input" << endl;
                cout << menu << endl;
                getline(cin, userChoise);
            }
            if (!InputValidation::menuCheck(choise))
            {
                cout << "invalid input" << endl;
                cout << menu << endl;
                getline(cin, userChoise);
            }
            else
            {
                break;
            }
        } while (!InputValidation::menuCheck(choise));

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
            getline(cin, fileName);
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
            send(sock, &fileSize, sizeof(fileSize), 0);
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
            getline(cin, fileNameTrain);

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
            send(sock, &fileSizeTrain, sizeof(fileSizeTrain), 0);

            // Send the file
            memset(buffer, 0, sizeof(buffer));

            while (fileTrain)
            {
                memset(buffer, 0, sizeof(buffer));

                fileTrain.read(buffer, sizeof(buffer));
                int bytes_read = fileTrain.gcount();
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
        if (data_len == 1 && userChoise == "3")
        {
            recv(sock, buffer, 1, 0);
            string result = string(buffer, 1);
            memset(buffer, 0, sizeof(buffer));
            if (result == "1")
            {
                cout << "please upload data" << endl;
                continue;
            }

            recv(sock, buffer, 25, 0);
            cout << buffer << endl;
            memset(buffer, 0, sizeof(buffer));
        }

        if (data_len == 1 && userChoise == "4")
        {

            recv(sock, buffer, 1, 0);
            string result = string(buffer, 1);
            memset(buffer, 0, sizeof(buffer));
            if (result == "1")
            {
                cout << "please upload data" << endl;
                continue;
            }
            if (result == "2")
            {
                cout << "please classify the data" << endl;
                continue;
            }

            memset(buffer, 0, sizeof(buffer));

            string fileTrain;
            int fileSize = 0;
            // recive the file size
            recv(sock, &fileSize, sizeof(fileSize), 0);

            // recive all of the packets in the size of the buffer
            for (int i = 0; i < ((fileSize - 1) / sizeof(buffer)); i++)
            {
                memset(buffer, 0, sizeof(buffer));
                int bytes = recv(sock, buffer, sizeof(buffer), 0);
                fileTrain += string(buffer, bytes);
            }

            // recive the last packet that is smaller then the buffer size
            int bytes = recv(sock, buffer, fileSize % sizeof(buffer), 0);
            fileTrain += string(buffer, bytes);
            cout << fileTrain;
        }

        if (data_len == 1 && userChoise == "5")
        {
            recv(sock, buffer, 1, 0);
            string result = string(buffer, 1);
            memset(buffer, 0, sizeof(buffer));
            if (result == "1")
            {
                cout << "please upload data" << endl;
                continue;
            }
            if (result == "2")
            {
                cout << "please classify the data" << endl;
                continue;
            }
            string filePath;
            cin >> filePath;

            char buffer[4096];
            memset(buffer, 0, sizeof(buffer));
            string fileTrain;
            int fileSize = 0;
            // recive the file size
            recv(sock, &fileSize, sizeof(fileSize), 0);

            // recive all of the packets in the size of the buffer
            for (int i = 0; i < ((fileSize - 1) / sizeof(buffer)); i++)
            {
                memset(buffer, 0, sizeof(buffer));
                int bytes = recv(sock, buffer, sizeof(buffer), 0);
                fileTrain += string(buffer, bytes);
            }
            // recive the last packet that is smaller then the buffer size
            int bytes = recv(sock, buffer, fileSize % sizeof(buffer), 0);
            fileTrain += string(buffer, bytes);
            ofstream outfile(filePath);
            outfile << fileTrain;
            outfile.close();
        }
        if (data_len == 1 && userChoise == "8")
        {
            break;
        }
    }
    close(sock);
    return 0;
}

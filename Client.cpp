#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <limits>

#define MENU_SIZE 187

using namespace std;

int main(int argc, char *argv[])
{
    const char *ip_address = argv[1];
    // CHECK if the input string is a valid IP address:
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
    if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("error connecting to server");
    }
    int stop;
    int data_len;
    string input;
    while (true)
    {

        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));

        recv(sock, buffer, MENU_SIZE, 0);

        cout << buffer << endl;
        string menu = string(buffer, MENU_SIZE);

        memset(buffer, 0, sizeof(buffer));

        getline(cin, input);

        while (input.empty() || !input.compare(""))
        {

            getline(cin, input);
        }

        while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "8")
        {
            cout << "invalid input" << endl;

            cout << menu << endl;
            getline(cin, input);
        }

        try
        {
            stop = stod(input);
            if (stop == -1)
            {
                break;
            }
        }
        catch (...)
        {
        }

        data_len = input.length();
        int sent_bytes = send(sock, input.c_str(), data_len, 0);

        if (sent_bytes < 0)
        {
            perror("error in sending");
        }

        if (data_len == 1 && input == "1")
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
            send(sock, (char *)&fileSize, sizeof(fileSize), 0);

            // Send the file
            char buffer[4096];
            while (file)
            {
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
            send(sock, (char *)&fileSizeTrain, sizeof(fileSizeTrain), 0);

            // Send the file
            memset(buffer, 0, sizeof(buffer));

            while (fileTrain)
            {
                fileTrain.read(buffer, sizeof(buffer));
                int bytes_read = file.gcount();
                send(sock, buffer, bytes_read, 0);
            }
            fileTrain.close();
            memset(buffer, 0, sizeof(buffer));

            // recive Upload complete.
            recv(sock, buffer, sizeof("Upload complete.\n"), 0);
            cout << buffer;
        }

        if (data_len == 1 && input == "2")
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

                send(sock, "EMPTY", 6, 0);
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

        if (data_len == 1 && input == "8")
        {

            break;
        }
    }
    close(sock);
    return 0;
}

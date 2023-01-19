#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
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
        getline(cin, input);
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
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0)
        {
            perror("connection is closed");
        }
        else if (read_bytes < 0)
        {
            perror("error in receving from server");
        }
        else
        {
            cout << buffer << "\n";
            memset(buffer, 0, read_bytes);
        }
    }
    close(sock);
    return 0;
}

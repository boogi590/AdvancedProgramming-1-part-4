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

using namespace std;
/*
 *creating a TCP server to accept from client vector, distance function and K for KNN algorithem. returning KNN result to client.
 *wating for clients to connet in infinite loop.
 */
int main(int argc, char *argv[])
{
    string classification;
    if (argc != 3)
    {
        cout << "wrong number of arguments. there should be 3 arguments" << endl;
        return 0;
    }
    // create the data base
    multimap<vector<double>, string> dataBase;
    dataBase = DataBase::createDataBaseFromFIle(argv[1]); // argv[1] should be file name of the data base.
    if (dataBase.empty())
    {
        cout << "an error has occurred in the data base" << endl;
        return 0;
    }
    int temp = 0;
    try
    {
        temp = stoi(argv[2]); // argv[2] should be the port to listen to.
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
        }
        while (true)
        {
            char buffer[4096];
            memset(buffer, 0, sizeof(buffer));
            bool invalidFlag = false;
            string classification;
            int expected_data_len = sizeof(buffer);
            int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
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
                istringstream iss(buffer); // creating a istringstream to extract from client output the vector, string that represents distance function and K for KNN algorithem.
                vector<double> vec;
                string distanceFunction = " ";
                int k = 0;

                // Extract the double vector
                double x;
                while (iss >> x)
                {
                    vec.push_back(x);
                }
                if (iss.fail())
                {
                    // reset the state of the stringstream
                    iss.clear();
                }

                // Extract the string
                iss >> distanceFunction;

                // Extract the integer
                iss >> k;

                if (k <= 0)
                {
                    invalidFlag = true;
                    classification = "invalid input";
                }
                // CHECK: If K is greater than the number of vectors in the database we define him to be the size of the database.
                if (k > dataBase.size())
                {
                    k = dataBase.size();
                }

                // CHECK: if the input vector is not the same length as the vectors in the database.
                if (!InputValidation::isVectorsLengthEquals(vec, dataBase.begin()->first))
                {
                    invalidFlag = true;
                    classification = "invalid input";
                }

                // CHECK: if the user entered a non-existent distance function - not one of the existing options.
                vector<double> v1 = {1, 2};
                vector<double> v2 = {2, 3};

                double tempDistance = Distance::distanceAcorddingTo(v1, v2, distanceFunction);
                if (tempDistance == -1)
                {
                    invalidFlag = true;
                    classification = "invalid input";
                }

                if (!invalidFlag)
                {

                    KNN calculateKNN(k, dataBase, distanceFunction);
                    classification = calculateKNN.KNN::mostCommonFromK(vec);
                }
            }
            int sent_bytes = send(client_sock, classification.c_str(), classification.length(), 0);
            if (sent_bytes < 0)
            {
                perror("error sending to client");
            }
        }
        close(client_sock);
    }
    close(sock);
    return 0;
}

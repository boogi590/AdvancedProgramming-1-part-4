#include "UploadCommand.h"
#include "DataBase.h"
#include "string.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include <iostream>
UploadCommand::UploadCommand(SocketIO socket)
{

    this->socket = socket;
}

void UploadCommand::execute()
{
    string description = "Please upload your local train CSV file.";
    send(socket.getSock(), description.c_str(), description.length(), 0);
    int fileSizeTrain = 0;
    int bytes_received_total = 0;
    string fileTrain;
    char buffer[4096];

    // Receive the file size
    recv(socket.getSock(), (char *)&fileSizeTrain, sizeof(fileSizeTrain), 0);

    // Receive the file
    while (bytes_received_total < fileSizeTrain)
    {
        memset(buffer, 0, sizeof(buffer));

        int bytes_received = recv(socket.getSock(), buffer, sizeof(buffer), 0);
        bytes_received_total += bytes_received;
        fileTrain += string(buffer, sizeof(buffer));
    }

    this->dataBase = DataBase::createDataBaseFromFIle(fileTrain);

    cout << fileTrain << endl;

    string upload = "Upload complete.\n";
    send(socket.getSock(), upload.c_str(), upload.length(), 0);

    string testString = "Please upload your local test CSV file.\n";
    send(socket.getSock(), testString.c_str(), testString.length(), 0);

    int fileSizeTest = 0;
    bytes_received_total = 0;
    string fileTest;
    memset(buffer, 0, sizeof(buffer));
    // Receive the file size
    recv(socket.getSock(), (char *)&fileSizeTest, sizeof(fileSizeTest), 0);

    // Receive the file
    while (bytes_received_total < fileSizeTest)
    {
        int bytes_received = recv(socket.getSock(), buffer, sizeof(buffer), 0);
        bytes_received_total += bytes_received;
        fileTest += string(buffer, sizeof(buffer));
    }
    this->test = fileTest;
    cout << fileTest << endl;
}

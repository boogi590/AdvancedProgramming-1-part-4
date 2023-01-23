#include "UploadCommand.h"

UploadCommand::UploadCommand(SocketIO socket, multimap<vector<double>, string> &database,
                             vector<vector<double>> &test) : socket(socket),
                                                             database(database),
                                                             test(test)

{
}

void UploadCommand::execute()
{
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

    this->database = DataBase::createDataBaseFromString(fileTrain);

    // cout << fileTrain << endl;

    string upload = "Upload complete.\nPlease upload your local test CSV file.";
    send(socket.getSock(), upload.c_str(), upload.length(), 0);

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
    this->test = DataBase::createTestVectors(fileTest);
    //  cout << fileTest;

    string uploadTest = "Upload complete.\n";
    send(socket.getSock(), uploadTest.c_str(), uploadTest.length(), 0);
}

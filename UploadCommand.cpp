#include "UploadCommand.h"

UploadCommand::UploadCommand(SocketIO socket, multimap<vector<double>, string> &database,
                             vector<vector<double>> &test, FlowControl &flowC) : socket(socket),
                                                                                 database(database),
                                                                                 test(test),
                                                                                 flowC(flowC)

{
}

void UploadCommand::execute()
{
    string train = "Please upload your local train CSV file.";

    send(socket.getSock(), train.c_str(), train.length(), 0);
    int fileSizeTrain = 0;
    int bytes_received_total = 0;
    string fileTrain;
    char buffer[4096];

    // Receive the file size
    int bytes = recv(socket.getSock(), (char *)&fileSizeTrain, sizeof(fileSizeTrain), 0);

    if (fileSizeTrain <= 0)
    {
        return;
    }

    if (bytes <= 0)
    {
        close(socket.getSock());
    }

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
    bytes = recv(socket.getSock(), (char *)&fileSizeTest, sizeof(fileSizeTest), 0);

    if (fileSizeTest <= 0)
    {
        return;
    }
    if (bytes <= 0)
    {
        close(socket.getSock());
    }
    // Receive the file
    while (bytes_received_total < fileSizeTest)
    {
        memset(buffer, 0, sizeof(buffer));

        int bytes_received = recv(socket.getSock(), buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            close(socket.getSock());
        }
        cout << "bytes_received_total" << bytes_received_total << endl;
        bytes_received_total += bytes_received;
        fileTest += string(buffer, sizeof(buffer));
    }
    this->test = DataBase::createTestVectors(fileTest);

    // cout << fileTest;
    this->flowC.setDidFilesUploaded(true);
    this->flowC.setDidDataClassified(false);

    string uploadTest = "Upload complete.\n";
    send(socket.getSock(), uploadTest.c_str(), uploadTest.length(), 0);
}
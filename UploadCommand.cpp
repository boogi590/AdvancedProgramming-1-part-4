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
    // send to client to upload local train file
    string train = "Please upload your local train CSV file.";
    socket.write(train);

    int fileSizeTrain = 0;
    string fileTrain;
    char buffer[4096];

    // read the file size the client sent
    string fileSize = socket.read();
    try
    {
        fileSizeTrain = stoi(fileSize);
    }
    catch (...)
    {
        return;
    }
    if (fileSizeTrain <= 0)
    {
        return;
    }
    int bytes_received_total = 0;
    // Receive the file
    for (int i = 0; i < ((fileSizeTrain - 1) / sizeof(buffer)) + 1; i++)
    {
        fileTrain += socket.read();
    }

    string upload = "Upload complete.\nPlease upload your local test CSV file.";
    send(socket.getSock(), upload.c_str(), upload.length(), 0);

    int fileSizeTest = 0;
    bytes_received_total = 0;
    memset(buffer, 0, sizeof(buffer));
    // Receive the file size
    // read the file size the client sent
    string fileTest = socket.read();
    try
    {
        fileSizeTest = stoi(fileTest);
    }
    catch (...)
    {
        return;
    }
    if (fileSizeTest <= 0)
    {
        return;
    }

    // Receive the file
    for (int i = 0; i < ((fileSizeTest - 1) / sizeof(buffer)) + 1; i++)
    {
        fileTest += socket.read();
    }

    // create the data base
    this->database = DataBase::createDataBaseFromString(fileTrain);
    // create vector of double vectors of the test file
    this->test = DataBase::createTestVectors(fileTest);

    // set the flow control that files uploaded.
    this->flowC.setDidFilesUploaded(true);
    this->flowC.setDidDataClassified(false);

    string uploadTest = "Upload complete.\n";
    send(socket.getSock(), uploadTest.c_str(), uploadTest.length(), 0);
}
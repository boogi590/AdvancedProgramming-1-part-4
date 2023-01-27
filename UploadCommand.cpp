#include "UploadCommand.h"
#define BUFFER_SIZE 4096

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

    fileSizeTrain = socket.reciveSize();
    if (fileSizeTrain <= 0)
    {
        return;
    }
    // Receive the file
    for (int i = 0; i < ((fileSizeTrain - 1) / BUFFER_SIZE) + 1; i++)
    {
        string read = socket.read();
        fileTrain += read;
    }

    string upload = "Upload complete.\nPlease upload your local test CSV file.";
    // send to cleint that upload completed and that he should upload the test file now
    socket.write(upload);

    int fileSizeTrain = 0;
    string fileTest;

    fileSizeTrain = socket.reciveSize();
    if (fileSizeTrain <= 0)
    {
        return;
    }

    // Receive the file
    for (int i = 0; i < ((fileSizeTrain - 1) / BUFFER_SIZE) + 1; i++)
    {
        string read = socket.read();

        fileTest += read;
    }

    // create the data base
    this->database = DataBase::createDataBaseFromString(fileTrain);
    // create vector of double vectors of the test file
    this->test = DataBase::createTestVectors(fileTest);

    // set the flow control that files uploaded and need to be classified.
    this->flowC.setDidFilesUploaded(true);
    this->flowC.setDidDataClassified(false);

    string uploadTest = "Upload complete.\n";
    // send to client that uloade completed
    socket.write(uploadTest);
}
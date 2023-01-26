#include "SettingsCommand.h"
SettingsCommand::SettingsCommand(SocketIO socket, multimap<vector<double>, string> &database,
                                 int &k, string &distanceMatric) : socket(socket),
                                                                   database(database),
                                                                   k(k),
                                                                   distanceMatric(distanceMatric)

{
}

void SettingsCommand::execute()
{
    string error;
    this->description = "The current KNN parameters are: K = " + to_string(this->k) + ", DISTANCE METRIC = " + this->distanceMatric + "\n";
    socket.write(description);

    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    string input;
    input = socket.read();

    if (input.length() == 0)
    {
        return;
    }

    if (input == "EMPTY")
    {
        memset(buffer, 0, sizeof(buffer));
        return;
    }

    bool invaild = false;
    double tempK;
    string distanceFunc;
    stringstream stream(input);
    stream >> tempK;
    stream >> distanceFunc;

    if (!InputValidation::intOrDouble(tempK))
    {

        invaild = true;
        error = "invaild value for K\n";
    }
    if (tempK <= 0 && !invaild)
    {
        invaild = true;
        error = "invaild value for K\n";
    }
    // CHECK: If K is greater than the number of vectors in the database we define him to be the size of the database.
    if (tempK > database.size() && !invaild)
    {
        invaild = true;
        error = "invaild value for K\n";
    }

    // CHECK: if the user entered a non-existent distance function - not one of the existing options.
    vector<double> v1 = {1, 2};
    vector<double> v2 = {2, 3};

    double tempDistance = Distance::distanceAcorddingTo(v1, v2, distanceFunc);
    if (tempDistance == -1)
    {
        invaild = true;
        error += "invalid value for metric\n";
    }

    if (!invaild)
    {
        this->distanceMatric = distanceFunc;
        this->k = tempK;
        string changed = "changed";
        socket.write(changed);
    }
    else
    {
        socket.write(error);
    }
}
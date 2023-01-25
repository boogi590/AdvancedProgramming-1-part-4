#include "Command.h"
#include "SocketIO.h"
#include <map>
#include <vector>
#include "DataBase.h"
#include "string.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <iostream>
#include "DataBase.h"
#include "string.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
class UploadCommand : public Command
{
public:
    UploadCommand(SocketIO socket, multimap<vector<double>, string> &database, vector<vector<double>> &test);

    void execute() override;

private:
    string description;
    SocketIO socket;
    multimap<vector<double>, string> database;
    vector<vector<double>> test;
};

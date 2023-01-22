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

class UploadCommand : public Command
{
public:
    UploadCommand(SocketIO socket);
    void execute() override;

private:
    string description;
    SocketIO socket;
    multimap<vector<double>, string> dataBase;
    string test;
};

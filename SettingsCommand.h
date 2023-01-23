#include "Command.h"
#include "Distance.h"

#include "SocketIO.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

class SettingsCommand : public Command
{
public:
    SettingsCommand(SocketIO socket, multimap<vector<double>, string> &database, int &k, string &distanceMatric);
    void execute() override;

private:
    string description;
    SocketIO socket;
    int &k;
    string &distanceMatric;
    multimap<vector<double>, string> &database;
};

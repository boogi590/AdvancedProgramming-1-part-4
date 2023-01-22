#include "Command.h"
#include "SocketIO.h"
#include <map>
#include <vector>

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

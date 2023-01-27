#ifndef _CLI_H
#define _CLI_H
#include "Command.h"
#include "InputValidation.h"

class CLI
{
private:
    Command **commandArray;

public:
    CLI(Command *commandArray[]);
    void start(int commandNum);
    ~CLI();
};

#endif

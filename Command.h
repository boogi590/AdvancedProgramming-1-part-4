#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
#include "DefaultIO.h"

using namespace std;

class Command
{
public:
    virtual void execute() = 0;
    void setIO(DefaultIO *IO);

protected:
    string description;
    DefaultIO *IO;
};

#endif

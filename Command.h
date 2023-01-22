
#include <string>
#include "DefaultIO.h"
using namespace std;

class Command
{
public:
    virtual void execute() = 0;

protected:
    string description;
    DefaultIO *IO;
};

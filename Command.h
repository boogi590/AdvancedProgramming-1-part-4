
#include <string>

using namespace std;

class Command
{
public:
    virtual void execute() = 0;

private:
    string description;
};

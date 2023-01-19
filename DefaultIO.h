
#include <string>

using namespace std;

class DefaultIO
{
public:
    virtual string read() = 0;
    virtual void write(string input) = 0;
};

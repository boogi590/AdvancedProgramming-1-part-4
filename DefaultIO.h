#ifndef _DEFAULTIO_H
#define _DEFAULTIO_H
#include <string>

using namespace std;

class DefaultIO
{
public:
    virtual string read() = 0;
    virtual void write(string input) = 0;
    virtual void sendSize(int num) = 0;
};
#endif
#include "SocketIO.h"

#include <iostream>
SocketIO::SocketIO(int socket)
{
    this->socketNum = socket;
}

SocketIO::SocketIO()
{
}

string SocketIO::read()
{
}
void SocketIO::write(string)
{
}

int SocketIO::getSock()
{
    return this->socketNum;
}

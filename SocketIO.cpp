#include "SocketIO.h"
/**
 *constructor.
 *socket = the number of the socket.
 */
SocketIO::SocketIO(int socket)
{
    this->socketNum = socket;
}

/**
 * getter.
 */
int SocketIO::getSock()
{
    return this->socketNum;
}
/**
 * the function read from the socket.
 * @return string = the string of data from the socket.
 */
string SocketIO::read(char* writeTo)
{
    int bytes = recv(socketNum, writeTo, sizeof(writeTo), 0);
    if (writeTo <= 0)
    {
        return;
    }

    if (bytes <= 0)
    {
        close(socketNum);
    }
}
/**
 *
 */
void SocketIO::write(string output)
{
    send(socketNum, output.c_str(), output.length(), 0);
}

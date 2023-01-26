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
string SocketIO::read()
{
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    int bytesRead = recv(socketNum, buffer, sizeof(buffer), 0);
    if (bytesRead <= 0)
    {
        close(socketNum);
    }
    string recived = string(buffer, bytesRead);

    return recived;
}
/**
 *
 */
void SocketIO::write(string output)
{
    send(socketNum, output.c_str(), output.length(), 0);
}

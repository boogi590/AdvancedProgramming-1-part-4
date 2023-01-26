#ifndef _SOCKETIO_H
#define _SOCKETIO_H
#include "DefaultIO.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "string.h"

class SocketIO : public DefaultIO
{
private:
    int socketNum;

private:
    int socketNum;

public:
    // constructor.
    // constructor.
    SocketIO(int sokcet);

    // getter.
    int getSock();

    // getter.
    int getSock();

    // The implementation of the abstract class.
    string read();
    void write(string) override;
};
#endif
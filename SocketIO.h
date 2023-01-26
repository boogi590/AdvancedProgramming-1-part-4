#ifndef _SOCKETIO_H
#define _SOCKETIO_H
#include "DefaultIO.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

class SocketIO : public DefaultIO
{
private:
    int socketNum;

public:
    // constructor.
    SocketIO(int sokcet);

    // getter.
    int getSock();

    // The implementation of the abstract class.
    string read();
    string read(char* writeTo);
    void write(string) override;
};
#endif
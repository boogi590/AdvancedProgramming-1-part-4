#ifndef _SOCKETIO_H
#define _SOCKETIO_H
#include "DefaultIO.h"

class SocketIO : public DefaultIO
{
public:
    SocketIO(int sokcet);
    SocketIO();

    string read() override;
    void write(string) override;
    int getSock();

private:
    int socketNum;
};
#endif
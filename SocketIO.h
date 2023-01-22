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

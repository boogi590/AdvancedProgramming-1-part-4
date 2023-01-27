#include "Command.h"
#include "FlowControl.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
class DisplayResults : public Command
{
private:
    // classify_data = map of key = int and value =string such that the key =the line in the test CSV file and
    // value =the classifion of the vector in this line.
    map<int, string> &classify_data;
    FlowControl &flow_control;

public:
    void execute();
    DisplayResults(map<int, string> &calssify_data, FlowControl &fc);
};

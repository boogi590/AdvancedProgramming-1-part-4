#include "Command.h"
#include "FlowControl.h"
#include <algorithm>
#include <iostream>
#include <map>
#include "pthread.h"

using namespace std;

class DownloadResults : public Command
{
private:
    map<int, string> &classify_data;
    FlowControl &flow_control;

public:
    DownloadResults(map<int, string> &classify_data, FlowControl &fc);
    ~DownloadResults();
    void execute();
};

#include "Command.h"
#include "KNN.h"
#include "FlowControl.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class ClassifyData : public Command
{
protected:
    const multimap<vector<double>, string> &database;
    const vector<vector<double>> &testCSV;
    int &k;
    string &distance_metric;
    FlowControl flow_control;

public:
    ClassifyData(const multimap<vector<double>, string> &database, const vector<vector<double>> &testCSV, int &k, string &distance_metric, FlowControl &fc);
    void execute();
};

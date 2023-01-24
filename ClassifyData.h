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
    multimap<vector<double>, string> database;
    vector<vector<double>> testCSV;
    int k;
    string distance_metric;
    FlowControl flow_control;
    map<int, string> classify_data;

public:
    ClassifyData(multimap<vector<double>, string> &database,
                 vector<vector<double>> &testCSV,
                 int &k,
                 string &distance_metric,
                 FlowControl &fc,
                 map<int, string> &classify_data);
    void execute();
};

#include "Command.h"
#include <string>
#include <vector>
#include <map>
#include "KNN.h"
using namespace std;

class ClassifyData : public Command
{
protected:
    const multimap<vector<double>, string> &database;
    const vector<vector<double>> &testCSV;
    int &k;
    string &distance_metric;

public:
    ClassifyData(const multimap<vector<double>, string> &database, const vector<vector<double>> &testCSV, int &k, string &distance_metric);
    void execute();
};

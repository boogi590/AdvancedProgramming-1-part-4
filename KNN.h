#ifndef _KNN_H
#define _KNN_H
#include "Distance.h"
#include <map>
#include <algorithm>
using namespace std;
class KNN
{
public:
    KNN(int k, multimap<vector<double>, string> database, string whichD);
    string mostCommonFromK(vector<double> vec);

private:
    int k;
    multimap<vector<double>, string> database;
    string whichD;

    multimap<double, string> distanceFromVector(vector<double> vec);
};
#endif

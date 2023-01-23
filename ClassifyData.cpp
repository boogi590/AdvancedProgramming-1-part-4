#include "ClassifyData.h"

ClassifyData::ClassifyData(const multimap<vector<double>, string> &database,
                           const vector<vector<double>> &testCSV, int &k, string &distance_metric) : database(database),
                                                                                                     testCSV(testCSV),
                                                                                                     k(k),
                                                                                                     distance_metric(distance_metric)
{
}

void ClassifyData::execute()
{
    int line = 1;
    map<int, string> classify_data;
    KNN running_knn(k, database, distance_metric);
    for (auto testVec : testCSV)
    {
        classify_data.insert({line, running_knn.mostCommonFromK(testVec)});
        line++;
    }
    // IO.write("complete data classifying");
}
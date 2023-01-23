#include "ClassifyData.h"

ClassifyData::ClassifyData(const multimap<vector<double>, string> &database,
                           const vector<vector<double>> &testCSV, int &k, string &distance_metric, FlowControl &fc) : database(database),
                                                                                                                      testCSV(testCSV),
                                                                                                                      k(k),
                                                                                                                      distance_metric(distance_metric),
                                                                                                                      flow_control(fc)
{
}

void ClassifyData::execute()
{
    //if the user didnt upload files then return and print error.
    if (!flow_control.did_files_uploaded)
    {
        IO->write("please upload data");
        return;
    }
    int line = 1;
    map<int, string> classify_data;
    KNN running_knn(k, database, distance_metric);
    for (auto testVec : testCSV)
    {
        classify_data.insert({line, running_knn.mostCommonFromK(testVec)});
        line++;
    }
    IO->write("complete data classifying");
    flow_control.setDidDataClassified(true);
}
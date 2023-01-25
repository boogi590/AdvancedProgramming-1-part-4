#include "ClassifyData.h"

ClassifyData::ClassifyData(multimap<vector<double>, string> &database,
                           vector<vector<double>> &testCSV,
                           int &k,
                           string &distance_metric,
                           FlowControl &fc,
                           map<int, string> &classify_data) : database(database),
                                                              testCSV(testCSV),
                                                              k(k),
                                                              distance_metric(distance_metric),
                                                              flow_control(fc),
                                                              classify_data(classify_data)
{
}

void ClassifyData::execute()
{
    /**
    //if the user didnt upload files then return and print error.
    if (!flow_control.did_files_uploaded)
    {
        cout << "please upload data" << endl;
        IO->write("please upload data");
        return;
    }
    */
    int line = 1;
    KNN runningKnn(k, database, distance_metric);
    for (vector<vector<double>>::iterator vector = testCSV.begin(); vector != testCSV.end(); ++vector)
    {
        classify_data.insert({line, runningKnn.mostCommonFromK(*vector)});
        line++;
    }
    cout << "complete data classifying" << endl;
    cout << "classifyData size=" << classify_data.size() << endl;
    // IO->write("complete data classifying");
    // flow_control.setDidDataClassified(true);
}
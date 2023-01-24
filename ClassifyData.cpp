#include "ClassifyData.h"

ClassifyData::ClassifyData(multimap<vector<double>, string> &database,
                           vector<vector<double>> &testCSV,
                           int &k,
                           string &distance_metric,
                           FlowControl &fc,
                           map<int, string> &classify_data)
{
    this->database = database;
    this->testCSV = testCSV;
    this->k = k;
    this->distance_metric = distance_metric;
    this->flow_control = fc;
    this->classify_data = classify_data;
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
    cout << "hiiiiiiiiiiiiiiii" << endl;
    KNN running_knn(k, database, distance_metric);
    
    cout << sizeof(testCSV) << endl;
   
    cout << "complete data classifying" << endl;
    IO->write("complete data classifying");
    // flow_control.setDidDataClassified(true);
}
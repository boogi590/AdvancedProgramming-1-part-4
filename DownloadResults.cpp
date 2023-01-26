#include "DownloadResults.h"

DownloadResults::DownloadResults(map<int, string> &classify_data, FlowControl &fc) : classify_data(classify_data),
                                                                                     flow_control(fc)
{
}

DownloadResults::~DownloadResults()
{
}

void DownloadResults::execute()
{
       /**
    if(!flow_control.did_data_classified)
    {
        IO->write("please classify the data");
        return;
    }
     if(!flow_control.did_files_uploaded)
    {
        IO->write("please upload data");
        return;
    }
    */
    cout << "classifyData size=" << classify_data.size() << endl;
    for (map<int, string>::iterator mit = classify_data.begin(); mit != classify_data.end(); mit++)
    {
        pair<int, string> data = *mit;
        cout << to_string(data.first) << "    " << data.second << endl;
        // IO->write(to_string(data.first));
        // IO->write(" ");
        // IO->write(data.second);
        // IO->write("\n");
    }
}